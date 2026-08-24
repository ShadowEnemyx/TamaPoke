#pragma once

#include <Arduino.h>

// QMI8658 auf dem Waveshare I2C-Bus. Ohne Interrupt-Pin: nur pollen.
bool imuBegin();
bool imuOk();
void imuPoll(uint32_t nowMs, uint16_t intervalMs);
bool imuShakeEdge();          // einmaliger Impuls, verbraucht das Event
uint16_t imuTakeSteps();      // Delta seit dem letzten Aufruf
float imuLastMagG();          // letzte |a| in g, 0 wenn unbekannt
float imuLastGyroDps();       // letzte |gyro| in deg/s
uint8_t imuAddr();            // 0 wenn nicht gefunden
uint32_t imuPedometer();      // Rohzaehler des Chips
uint32_t imuSoftwarePedometer(); // eigener Zaehler aus Beschleunigungswerten
