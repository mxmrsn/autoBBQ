// Auto BBQ
//int fan_pin = 11;

//void setup() {
//  Serial.begin(9600);
//  pinMode(fan_pin, OUTPUT);
//
//}
//void loop() {
//digitalWrite(fan_pin, HIGH);
//  delay(2000);
//  digitalWrite(fan_pin , LOW);
//  delay(2000);
//}

#include "BBQFSM.h"

BBQstate next_state;    // next state
BBQ bbq;                // bbq object
BBQFSM fsm(bbq);       // finite state machine object

void setup()
{
  next_state = fsm.stepStateMachine(POWER_UP); // initialize BBQ finite state machine
}

//----------------------------------------------------------------//

void loop()
{
  next_state = fsm.stepStateMachine(next_state); // switch on state
}
