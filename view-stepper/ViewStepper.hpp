#pragma once
#include<AccelStepper.h>
#include<WiFiUdp.h>
#include<Arduino.h>
#include <Arduino_LSM6DS3.h>

// Quick and dirty stepper singleton.
class ViewStepper
{
 public:
  static ViewStepper* Instance();
  void setup(int pinA1, int pinA2, int pinB1, int pinB2);
  void setSpeed(int speed);
  void step(int count);
 private:
  ViewStepper();
  ViewStepper(ViewStepper const&);
  ViewStepper& operator=(ViewStepper const&){};
  static ViewStepper* instance;
  int A1,A2,B1,B2;
  char state = 0;
  
};
