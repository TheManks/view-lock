#include "VLock.hpp"
#include "secrets.h"
#include <Stepper.h>
#include <WiFiUdp.h>
#include <WiFiNINA.h>
#include <Arduino.h>
#include <Arduino_LSM6DS3.h>
VLock::VLock(Stepper* motor, WiFiUDP* conn)
{
  actuator = motor;
  connection = conn;
}

void VLock::connLoop()
{
  static const char LOCK = 1;
  static const char UNLOCK = 2;
  static const char STATUS = 0;

  int packetLen = connection->parsePacket();
  if(packetLen)
  {
    Serial.println("Got a message:");
    connection->read(msgBuffer, 17);
    char opcode = msgBuffer[0];
    Serial.println(opcode);
    Serial.println(LOCK);
    Serial.println(opcode == LOCK);
    switch(opcode)
    {
     case STATUS:
       status();
       break;
     case LOCK:
       lock();
       break;
     case UNLOCK:
       unlock();
       break;
     default:
       Serial.println("Got Garbage");
       break;
    }    
  }
}

void VLock::setup()
{
  int conn_stat = WL_IDLE_STATUS;

  actuator->setSpeed(5);
  
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }
  
  // attempt to connect to WiFi network:
  while ( conn_stat != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(LOCK_SSID);
    // Connect to WPA/WPA2 network:
    conn_stat = WiFi.begin(LOCK_SSID, LOCK_PASS);
    
    // wait 5 seconds for connection:
    delay(5000);
  }

  Serial.print("Connected to:");
  Serial.println(LOCK_SSID);

  Serial.println("Starting UDP Listener");
  connection->begin(LOCK_PORT);

  Serial.println("Init imu");
  
  if (!IMU.begin()) Serial.println("IMU did not initialize");
}

void VLock::status()
{
  // TODO: Give status code responses.
  return;
}

void VLock::lock()
{
  if(!getState())
  {
    Serial.println("Already locked");
    return;
  }
  Serial.println("Locking");
  actuator->step(512);
}

void VLock::unlock()
{
  if(getState())
  {
    Serial.println("Already unlocked");
    return;
  }
  Serial.println("Unlocking");
  actuator->step(-512);
}

bool VLock::getState()
{
  float x,y,z;
  while(!IMU.accelerationAvailable()){}

  IMU.readAcceleration(x, y, z);

  if(y > 0)
    return true;
  else
    return false;
}
