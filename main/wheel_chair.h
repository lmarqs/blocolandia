#include <Arduino.h>
#include <SoftwareSerial.h>

#include "h_bridge.h"

class WheelChairPilot {
 private:
  int32_t rotationWeight = 0;
  int32_t *rotationSpeeds = new int32_t[4]{0, 0, 0, 0};

  int32_t translationWeight = 0;
  int32_t *translationSpeeds = new int32_t[4]{0, 0, 0, 0};

 public:
  static inline int32_t MAX_AXIS_VALUE = 512;

  void calculateTranslation(int32_t axisX, int32_t axisY, int32_t normal) {
    this->translationWeight = normal;
    int32_t *speeds = this->translationSpeeds;

    if (axisX >= 0 && axisY <= 0) {
      speeds[0] = speeds[2] = -axisY - axisX;
      speeds[1] = speeds[3] = +normal;
    }

    if (axisX >= 0 && axisY >= 0) {
      speeds[0] = speeds[2] = -normal;
      speeds[1] = speeds[3] = -axisY + axisX;
    }

    if (axisX <= 0 && axisY >= 0) {
      speeds[0] = speeds[2] = -axisY - axisX;
      speeds[1] = speeds[3] = -normal;
    }

    if (axisX <= 0 && axisY <= 0) {
      speeds[0] = speeds[2] = +normal;
      speeds[1] = speeds[3] = -axisY + axisX;
    }
  }

  void calculateRotation(int32_t axisX, int32_t axisY, int32_t normal) {
    this->rotationWeight = normal;
    int32_t *speeds = this->rotationSpeeds;

    if (axisX >= 0 && axisY <= 0) {
      speeds[0] = speeds[3] = -axisY - axisX;
      speeds[1] = speeds[2] = +normal;
    }

    if (axisX >= 0 && axisY >= 0) {
      speeds[0] = speeds[3] = -normal;
      speeds[1] = speeds[2] = -axisY + axisX;
    }

    if (axisX <= 0 && axisY >= 0) {
      speeds[0] = speeds[3] = -axisY - axisX;
      speeds[1] = speeds[2] = -normal;
    }

    if (axisX <= 0 && axisY <= 0) {
      speeds[0] = speeds[3] = +normal;
      speeds[1] = speeds[2] = -axisY + axisX;
    }
  }

  void drive(HBridge *motor, int32_t i, int32_t maxValue) {
    int32_t speed = rotationWeight + translationWeight
                        ? (rotationSpeeds[i] * rotationWeight + translationSpeeds[i] * translationWeight) /
                              (rotationWeight + translationWeight)
                        : 0;

    motor->move(map(speed, 0, MAX_AXIS_VALUE, 0, maxValue));
  }
};
