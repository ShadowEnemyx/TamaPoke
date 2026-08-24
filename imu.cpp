#include "imu.h"
#include "pin_config.h"

#include <math.h>
#include <Wire.h>
#include <SensorQMI8658.hpp>

#include "time_utils.h"

static SensorQMI8658 qmi;
static bool ok = false;
static uint8_t foundAddr = 0;
static uint32_t lastPoll = 0;
static uint32_t bootIgnoreUntil = 0;
static uint32_t shakeIgnoreUntil = 0;
static bool shakePending = false;
static float lastMag = 0;
static float lastGyro = 0;
static uint32_t lastPed = 0;
static bool pedInited = false;
static uint16_t stepBank = 0;
static uint32_t softPed = 0;
static float walkGravity = 0;
static bool walkPeak = false;
static uint32_t walkLastPeak = 0;
static uint8_t walkCadence = 0;

bool imuOk() {
  return ok;
}

float imuLastMagG() {
  return lastMag;
}

float imuLastGyroDps() {
  return lastGyro;
}

uint8_t imuAddr() {
  return foundAddr;
}

uint32_t imuPedometer() {
  return lastPed;
}

uint32_t imuSoftwarePedometer() {
  return softPed;
}

static void bankSteps(uint16_t count) {
  uint32_t next = (uint32_t)stepBank + count;
  stepBank = next > 60000UL ? 60000 : (uint16_t)next;
  softPed += count;
}

static void detectSoftwareStep(uint32_t nowMs, float mag) {
  if (walkGravity <= 0.01f) {
    walkGravity = mag;
    return;
  }

  float signal = mag - walkGravity;
  float motion = fabsf(signal);
  // In Ruhe folgt die Basislinie zuegig der Sensorabweichung. Bei Bewegung
  // bleibt sie traege, damit der Gehimpuls nicht weggefiltert wird.
  float alpha = motion < 0.08f ? 0.12f : 0.025f;
  walkGravity += (mag - walkGravity) * alpha;
  if (deadlineActive(nowMs, bootIgnoreUntil)) return;

  // Nach jedem Impuls muss die Bewegung erst abklingen. Das verhindert, dass
  // Aufprall und Rueckschwung desselben Schritts doppelt gezaehlt werden.
  if (walkPeak) {
    if (signal <= 0.025f) walkPeak = false;
    return;
  }
  // Nur den positiven Aufprall zaehlen. Der anschliessende negative Ausschlag
  // ist Teil desselben Schritts und darf keinen zweiten Impuls erzeugen.
  if (signal < 0.085f) return;
  walkPeak = true;

  uint32_t gap = walkLastPeak ? nowMs - walkLastPeak : 0;
  if (walkLastPeak && gap < 280UL) return;
  if (!walkLastPeak || gap > 1400UL) {
    walkLastPeak = nowMs;
    walkCadence = 1;
    return;
  }

  walkLastPeak = nowMs;
  if (walkCadence == 1) {
    // Erst zwei rhythmische Impulse bestaetigen Gehen; dann die beiden ersten
    // Schritte gemeinsam freigeben. Einzelne Stoesse bleiben wirkungslos.
    bankSteps(2);
    walkCadence = 2;
  } else {
    bankSteps(1);
    if (walkCadence < 255) walkCadence++;
  }
}

static bool probeAndStart(uint8_t addr) {
  if (!qmi.begin(Wire, addr, IIC_SDA, IIC_SCL)) return false;
  // Der Hardware-Pedometer ist fuer 2G / 62,5 Hz abgestimmt (wie im offiziellen
  // SensorLib-Beispiel). Mit 4G / 125 Hz blieben seine Zeit- und
  // Spitzenschwellen auf echter Hardware praktisch stumm.
  qmi.configAccelerometer(SensorQMI8658::ACC_RANGE_2G,
                          SensorQMI8658::ACC_ODR_62_5Hz,
                          SensorQMI8658::LPF_MODE_0);
  qmi.configGyroscope(SensorQMI8658::GYR_RANGE_512DPS,
                      SensorQMI8658::GYR_ODR_112_1Hz,
                      SensorQMI8658::LPF_MODE_3);
  qmi.enableAccelerometer();
  qmi.enableGyroscope();
  delay(40);
  foundAddr = addr;
  return true;
}

bool imuBegin() {
  ok = false;
  foundAddr = 0;
  lastMag = 0;
  lastGyro = 0;
  lastPed = 0;
  pedInited = false;
  stepBank = 0;
  softPed = 0;
  walkGravity = 0;
  walkPeak = false;
  walkLastPeak = 0;
  walkCadence = 0;
  shakePending = false;
  lastPoll = 0;

  // Board-Schema: 0x6B. 0x6A ist die alternative SA0-Adresse.
  if (!probeAndStart(QMI8658_L_SLAVE_ADDRESS) &&
      !probeAndStart(QMI8658_H_SLAVE_ADDRESS)) {
    Serial.println("QMI8658 no detectado");
    return false;
  }

  // Vier zusammenhaengende Schritte reichen fuer den Einstieg; der Sensor
  // meldet jeden validierten Schritt sofort statt in Viererpaketen. So werden
  // kurze Gehstrecken im Haus sichtbar, ohne beliebiges Schuetteln zu zaehlen.
  qmi.configPedometer(50, 200, 100, 200, 20, 4, 0, 1);
  if (qmi.enablePedometer()) {
    lastPed = qmi.getPedometerCounter();
    pedInited = true;
  }
  // Pedometer-Config kann Accel/Gyro ausmachen: wieder anschalten.
  qmi.enableAccelerometer();
  qmi.enableGyroscope();

  bootIgnoreUntil = millis() + 400;
  ok = true;
  Serial.printf("QMI8658 ok addr=0x%02X id=0x%X ped=%d\n",
                foundAddr, qmi.getChipID(), pedInited);
  return true;
}

void imuPoll(uint32_t nowMs, uint16_t intervalMs) {
  if (!ok) return;
  if (intervalMs < 25) intervalMs = 25;
  if (lastPoll && (uint32_t)(nowMs - lastPoll) < intervalMs) return;
  lastPoll = nowMs ? nowMs : 1;

  // getDataReady() ist unzuverlaessig, wenn Accel- und Gyro-ODR nicht identisch
  // sind (steht so in SensorLib). Rohregister lesen reicht fuer Shake.

  float x = 0, y = 0, z = 0;
  bool accelRead = qmi.getAccelerometer(x, y, z);
  if (accelRead) {
    lastMag = sqrtf(x * x + y * y + z * z);
    detectSoftwareStep(nowMs, lastMag);
  }
  float gx = 0, gy = 0, gz = 0;
  if (qmi.getGyroscope(gx, gy, gz)) {
    lastGyro = sqrtf(gx * gx + gy * gy + gz * gz);
  }

  // Ruhe ~1 g. Ein normaler Ball-Schuettler liegt oft nur bei 1.4-1.8 g;
  // Gyro faengt Drehen im Gehaeuse besser als der Accel allein.
  bool hot = lastMag >= 1.45f || lastGyro >= 80.0f;
  if (deadlineActive(nowMs, bootIgnoreUntil)) {
    return;
  }
  // Die Schuettel-Entprellung darf nur das Shake-Event blockieren, nicht das
  // Pedometer. Sonst konnte Gehen bei eingeschaltetem Display alle 40/80 ms
  // die Schritt-Abfrage ueberspringen.
  if (hot && !deadlineActive(nowMs, shakeIgnoreUntil)) {
    shakePending = true;
    shakeIgnoreUntil = nowMs + 280;
  }

  // Der interne Zaehler bleibt als Diagnose sichtbar. Gezaehlt wird bewusst
  // nur die Software-Erkennung, weil der Hardware-Pedometer auf einigen Boards
  // trotz erfolgreicher Aktivierung dauerhaft bei null bleibt.
  if (pedInited) lastPed = qmi.getPedometerCounter();
}

bool imuShakeEdge() {
  bool hit = shakePending;
  shakePending = false;
  return hit;
}

uint16_t imuTakeSteps() {
  uint16_t n = stepBank;
  stepBank = 0;
  return n;
}
