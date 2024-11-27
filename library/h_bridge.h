#pragma once

#include <Arduino.h>

#include "pin.h"

class HBridge {
 private:
  uint8_t onLoopCount;

 protected:
  void signal();

 public:
  void onLoop(uint8_t whenToStop = 10);
  void move(int32_t value);
  virtual void stop();
  virtual void forward(int32_t value);
  virtual void backward(int32_t value);
};

class FullHBridge : public HBridge {
 private:
  OutPin *pwm, *in1, *in2;

 public:
  FullHBridge(OutPin* pwm, OutPin* in1, OutPin* in2);
  void begin();
  void stop();
  void forward(int32_t value);
  void backward(int32_t value);
};

class HalfHBridge : public HBridge {
 private:
  OutPin *pwm, *in1, *in2;

 public:
  HalfHBridge(OutPin* in1, OutPin* in2);
  void begin();
  void stop();
  void forward(int32_t value);
  void backward(int32_t value);
};
