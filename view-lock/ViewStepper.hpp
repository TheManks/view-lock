#pragma once
#include<AccelStepper.h>
#include<WiFiUdp.h>
#include<Arduino.h>
#include <Arduino_LSM6DS3.h>

// Quick and dirty stepper Class.
class ViewStepper
{
 public:
  ViewStepper(int spr, int pinA1, int pinA2, int pinB1, int pinB2);
  void setSpeed(float speed);
  void step(int count);
  void freeWheel();
 private:
  void oneStep(int dir);
  int a1,a2,b1,b2;
  char state = 0;
  int stepsPerRev;
  int period;
};
