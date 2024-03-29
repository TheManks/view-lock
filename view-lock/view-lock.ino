#include "ViewStepper.hpp"
#include <WiFiNINA.h>
#include <WiFiUdp.h>
#include "secrets.h"
#include "VLock.hpp"
#define IN1 4
#define IN2 5
#define IN3 2
#define IN4 3



// WIFI characteristics pulled from secrets.h
int status = WL_IDLE_STATUS;

WiFiUDP Udp;
ViewStepper actuator = ViewStepper(4096, IN1, IN2, IN3, IN4);
VLock vlock = VLock(&actuator, &Udp);


void setup() {
  Serial.begin(9600);
  
  setupActuator();
  vlock.setup();
}
void loop()
{
  vlock.connLoop();
  freeActuator();
}

void freeActuator()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setupActuator()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
