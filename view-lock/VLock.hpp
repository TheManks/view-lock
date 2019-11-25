#pragma once
#include "ViewStepper.hpp"
#include <WiFiUdp.h>
#include <Arduino.h>
#include <Arduino_LSM6DS3.h>

#define MSG_SIZE                    17
#define SPEED                       2 // TODO: Figure out if this is too fast.
#define IMU_LOCKED_THRESHOLD        0.8
#define IMU_UNLOCKED_THRESHOLD      -0.8


class VLock
{
 public:
  VLock(ViewStepper*, WiFiUDP*);
  void connLoop();
  void setup();
 private:
  
  ViewStepper* actuator;
  WiFiUDP* connection;
  char msgBuffer[17];
  void status();
  void lock();
  void unlock();
  bool getState();
  bool getDoneLocking();
  bool getDoneUnlocking();
};
