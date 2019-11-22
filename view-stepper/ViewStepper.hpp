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
 private:
  void oneStep(int dir);
  int A1,A2,B1,B2;
  char state = 0;
  int stepsPerRev;
  int eriod;
};
