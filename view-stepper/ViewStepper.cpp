#include<ViewStepper.hpp>
#include<Arduino.h>
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}
// The fact I have to do this is absurd. Remainder is dumb.
int modulo(int x,int N){
    return (x % N + N) %N;
}

ViewStepper::ViewStepper(int spr, int pinA1, int pinA2, int pinB1, int pinB2)
{
  A1 = pinA1;
  A2 = pinA2;
  B1 = pinB1;
  B2 = pinB2;
  stepsPerRev = spr;
  period = 0;
}
void ViewStepper::setSpeed(float speed)
{
  float stepsPerMsec = (((float) stepsPerRev)*speed)/60;
  curr_period = (int) (1/stepsPerMsec);
}
void ViewStepper::step(int steps)
{
  int sign = sgn(count);
  count = abs(count);
  for(int step = 0; step < steps; step++)
  {
    oneStep(sign);
    delay(curr_period);
  }
}

void ViewStepper::oneStep(int dir)
{
  switch(state)
  {
   case 0:
     digitalWrite(A1,HIGH);
     digitalWrite(A2,LOW);
     digitalWrite(B1,HIGH);
     digitalWrite(B2,LOW);
     break;
     
   case 1:
     digitalWrite(A1,LOW);
     digitalWrite(A2,HIGH);
     digitalWrite(B1,HIGH);
     digitalWrite(B2,LOW);
     break;
     
   case 2:
     digitalWrite(A1,LOW);
     digitalWrite(A2,HIGH);
     digitalWrite(B1,LOW);
     digitalWrite(B2,HIGH);
     break;
     
   case 3:
     digitalWrite(A1,LOW);
     digitalWrite(A2,HIGH);
     digitalWrite(B1,LOW);
     digitalWrite(B2,HIGH);
     break;
  }
  state = modulo(state+dir,4);
}

void ViewStepper::freeWheel()
{
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  digitalWrite(B1,LOW);
  digitalWrite(B2,LOW);
}
