#pragma once
#include<Stepper.h>
#include<WiFiUdp.h>
#include<Arduino.h>

#define MSG_SIZE  17
#define SPEED     5 // TODO: Figure out if this is too fast.

class VLock
{
 public:
  VLock(Stepper*, WiFiUDP*);
  void connLoop();
  void setup();
 private:
  
  Stepper* actuator;
  WiFiUDP* connection;
  char msgBuffer[17];
  void status();
  void lock();
  void unlock();
  void getState();
};
