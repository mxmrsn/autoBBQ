// Auto BBQ
#include "BBQFSM.h"

BBQstate next_state;    // next state
BBQ bbq;                // bbq object
BBQFSM fsm(bbq);        // finite state machine

void setup()
{
  next_state = fsm.stepStateMachine(POWER_UP); // initialize BBQ finite state machine
}

//----------------------------------------------------------------//

void loop()
{
  next_state = fsm.stepStateMachine(next_state); // switch on state
}
