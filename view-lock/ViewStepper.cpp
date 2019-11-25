#include "ViewStepper.hpp"
#include "Arduino.h"
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
// The fact I have to do this is absurd. Remainder is dumb.
char modulo(char x, char N){
    return (x % N + N) %N;
}

ViewStepper::ViewStepper(int spr, int pinA1, int pinA2, int pinB1, int pinB2)
{
  a1 = pinA1;
  a2 = pinA2;
  b1 = pinB1;
  b2 = pinB2;
  stepsPerRev = spr;
  period = 0;
}
void ViewStepper::setSpeed(float speed)
{
  float stepsPerMsec = (((float) stepsPerRev)*speed)/60000;
  period = (int) (1/stepsPerMsec);
}
void ViewStepper::step(int steps)
{
  int sign = sgn(steps);
  int count = abs(steps);
  for(int step = 0; step < count; step++)
  {
    oneStep(sign);
    delay(period);
  }
}

void ViewStepper::oneStep(int dir)
{
  switch(state)
  {
   case 0:
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     break;
     
   case 1:
     digitalWrite(a1,LOW);
     digitalWrite(a2,HIGH);
     digitalWrite(b1,HIGH);
     digitalWrite(b2,LOW);
     break;
     
   case 2:
     digitalWrite(a1,LOW);
     digitalWrite(a2,HIGH);
     digitalWrite(b1,LOW);
     digitalWrite(b2,HIGH);
     break;
     
   case 3:
     digitalWrite(a1,HIGH);
     digitalWrite(a2,LOW);
     digitalWrite(b1,LOW);
     digitalWrite(b2,HIGH);
     break;
  }
  state = modulo(state+dir,4);
}

void ViewStepper::freeWheel()
{
  digitalWrite(a1,LOW);
  digitalWrite(a2,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(b2,LOW);
}
