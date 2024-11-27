#include <Arduino.h>
#include <Dabble.h>

#include "digital_pin.h"
#include "analog_pin.h"
#include "h_bridge.h"
#include "wheel_chair.h"

AnalogOutPin in11(03);
DigitalOutPin in12(12);

AnalogOutPin in21(11);
DigitalOutPin in22(13);

FullHBridge MotorL(&in11, &in11, &in12);
FullHBridge MotorR(&in21, &in21, &in22);

WheelChairPilot Pilot;

const uint8_t MAX_AXIS_RADIUS = 0b111 * 100;
const uint8_t MAX_MOTOR_SPEED = 100;

void setup() {
  Serial.begin(9600);
  Dabble.begin(9600, 02, 10);
  MotorL.begin();
  MotorR.begin();
}

void loop() {
  Dabble.processInput();
  MotorL.onLoop();
  MotorR.onLoop();

  Pilot.calculateTranslation(0, 0, 0);

  if (GamePad.isUpPressed() || GamePad.isCrossPressed()) {
    Pilot.calculateTranslation(0, +WheelChairPilot::MAX_AXIS_VALUE, WheelChairPilot::MAX_AXIS_VALUE);
  }

  if (GamePad.isDownPressed() || GamePad.isCirclePressed()) {
    Pilot.calculateTranslation(0, -WheelChairPilot::MAX_AXIS_VALUE, WheelChairPilot::MAX_AXIS_VALUE);
  }

  if (GamePad.isLeftPressed()) {
    Pilot.calculateTranslation(-WheelChairPilot::MAX_AXIS_VALUE, 0, WheelChairPilot::MAX_AXIS_VALUE);
  }

  if (GamePad.isRightPressed()) {
    Pilot.calculateTranslation(+WheelChairPilot::MAX_AXIS_VALUE, 0, WheelChairPilot::MAX_AXIS_VALUE);
  }

  Pilot.calculateRotation(map(100 * GamePad.getXaxisData(), 0, 100 * 0b111, 0, WheelChairPilot::MAX_AXIS_VALUE),
                          map(100 * GamePad.getYaxisData(), 0, 100 * 0b111, 0, WheelChairPilot::MAX_AXIS_VALUE),
                          map(GamePad.getRadius(), 0, 0b111, 0, WheelChairPilot::MAX_AXIS_VALUE));

  Pilot.drive(&MotorR, 0, MAX_MOTOR_SPEED);
  Pilot.drive(&MotorL, 1, MAX_MOTOR_SPEED);
}
