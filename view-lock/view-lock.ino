#include<Stepper.h>
#include<WiFiNINA.h>
#include <WiFiUdp.h>
#include"secrets.h"
#include"VLock.hpp"
#define MotorInterfaceType 8
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9

#define C11 3
#define C12 2
#define C21 4
#define C22 5


// WIFI characteristics pulled from secrets.h
int status = WL_IDLE_STATUS;

WiFiUDP Udp;
AccelStepper actuator = AccelStepper(MotorInterfaceType, IN1, IN3, IN2, IN4);
VLock vlock = VLock(&actuator, &Udp);


void setup() {
  Serial.begin(9600);
  setupActuator();   
  while(true){
    digitalWrite(C11, HIGH);
    digitalWrite(C12, LOW);
    digitalWrite(C21, HIGH);
    digitalWrite(C22, LOW);
    delay(10);
    digitalWrite(C11, LOW);
    digitalWrite(C12, HIGH);
    digitalWrite(C21, HIGH);
    digitalWrite(C22, LOW);
    delay(10);
    digitalWrite(C11, LOW);
    digitalWrite(C12, HIGH);
    digitalWrite(C21, LOW);
    digitalWrite(C22, HIGH);
    delay(10);
    digitalWrite(C11, HIGH);
    digitalWrite(C12, LOW);
    digitalWrite(C21, LOW);
    digitalWrite(C22, HIGH);
    delay(10);
  }
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
  pinMode(C11, OUTPUT);
  pinMode(C12, OUTPUT);
  pinMode(C21, OUTPUT);
  pinMode(C22, OUTPUT);
}
