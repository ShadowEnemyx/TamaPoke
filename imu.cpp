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

static bool probeAndStart(uint8_t addr) {
  if (!qmi.begin(Wire, addr, IIC_SDA, IIC_SCL)) return false;
  // Wie das Waveshare-Demo: Accel schnell, dann Gyro. Pedometer danach,
  // weil dessen Config den Accel kurz abschaltet.
  qmi.configAccelerometer(SensorQMI8658::ACC_RANGE_4G,
                          SensorQMI8658::ACC_ODR_125Hz,
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
  shakePending = false;
  lastPoll = 0;

  // Board-Schema: 0x6B. 0x6A ist die alternative SA0-Adresse.
  if (!probeAndStart(QMI8658_L_SLAVE_ADDRESS) &&
      !probeAndStart(QMI8658_H_SLAVE_ADDRESS)) {
    Serial.println("QMI8658 no detectado");
    return false;
  }

  qmi.configPedometer(50, 200, 100, 200, 20, 10, 0, 4);
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
  if (qmi.getAccelerometer(x, y, z)) {
    lastMag = sqrtf(x * x + y * y + z * z);
  }
  float gx = 0, gy = 0, gz = 0;
  if (qmi.getGyroscope(gx, gy, gz)) {
    lastGyro = sqrtf(gx * gx + gy * gy + gz * gz);
  }

  // Ruhe ~1 g. Ein normaler Ball-Schuettler liegt oft nur bei 1.4-1.8 g;
  // Gyro faengt Drehen im Gehaeuse besser als der Accel allein.
  bool hot = lastMag >= 1.45f || lastGyro >= 80.0f;
  if (deadlineActive(nowMs, bootIgnoreUntil) || deadlineActive(nowMs, shakeIgnoreUntil)) {
    return;
  }
  if (hot) {
    shakePending = true;
    shakeIgnoreUntil = nowMs + 280;
  }

  if (!pedInited) return;
  uint32_t ped = qmi.getPedometerCounter();
  if (ped != lastPed) {
    uint32_t delta = ped - lastPed;
    lastPed = ped;
    if (delta > 0 && delta <= 80) {
      uint32_t next = (uint32_t)stepBank + delta;
      stepBank = next > 60000UL ? 60000 : (uint16_t)next;
    }
  }
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
