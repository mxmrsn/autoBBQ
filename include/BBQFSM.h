/*=========================================================================//
BBQ_FSM.h
Implements a finite state machine for the AutoBBQ
Designed for use with Teensy 3.1/3.2
//=========================================================================*/

// #ifndef BBQFSM_H
// #define BBQFSM_H

// #pragma once
#include "BBQ.h"
#include <unistd.h>

#define BBQ_VERSION 0.1

class BBQFSM
{

  public:

    enum BBQstate { POWER_UP, IDLE, AUTO_INIT, AUTO_CONTROL };

    BBQ bbq;
    BBQstate current_state; // current fsm state

    double delay_time = 1E4; // us
    int count = 0;
    void printCurrentState();

    // Auto BBQ
    BBQFSM(BBQ bbq_c);
    void printErrorCode(BBQ::ErrorCode error_code); // reads BBQ::getErrorCode() and prints message
    void blinkErrorCode(BBQ::ErrorCode error_code); // blinks green LEDs to signal error codes (1 Hz = WRONG_MODULE_ORDER; 2 Hz = ESTOP_TRIGGERED; 4 Hz = LIMIT_SWITCH_TRIGGERED_ON_STARTUP)

    // Finite State Machine
    BBQstate PowerUP();
    BBQstate Idle();
    BBQstate AutoInit();
    BBQstate AutoControl();
    BBQstate stepStateMachine(BBQstate state_next);

};

BBQFSM::BBQFSM(BBQ bbq_c) {
  bbq = bbq_c;
};

// Error code blinking
void BBQFSM::printCurrentState() {
    const char* state_name;

    switch (current_state) {
        case POWER_UP:
            state_name = "Power Up";
            break;
        case IDLE:
            state_name = "Idle";
            break;
        case AUTO_INIT:
            state_name = "Auto Init";
            break;
        case AUTO_CONTROL:
            state_name = "Auto Control";
            break;
        default:
            state_name = "Error determining state";
            break;
    }

    std::cout<<"Current State: "<<state_name<<std::endl;
};
void BBQFSM::printErrorCode(BBQ::ErrorCode error_code){

  switch (error_code) {
      case BBQ::ErrorCode::NO_ERROR:
          // Serial.println("\nThere is currently no error :)");
          std::cout << "\nThere is currently no error :)" << std::endl;
          break;

      default:
          // Serial.println("\nSomething might be wrong, but I'm not sure...");
          std::cout << "\nSomething might be wrong, but I'm not sure..." << std::endl;
          break;
  }};
void BBQFSM::blinkErrorCode(BBQ::ErrorCode error_code){
    // 1 Hz = WRONG_MODULE_ORDER
    // 2 Hz = ESTOP_TRIGGERED
    // 4 Hz = LIMIT_SWITCH_TRIGGERED_ON_STARTUP

    switch (error_code) {
    case BBQ::ErrorCode::OVER_TEMP:
        std::cout<<"Over Temp!"<<std::endl;
        // timerMotorSelectLed.begin([]() {bbq.toggleLEDG();}, 500000); // 1 Hz
        break;
    case BBQ::ErrorCode::LOW_FUEL:
        std::cout<<"Low Fuel!"<<std::endl;
        // timerMotorSelectLed.begin([]() {bbq.toggleLEDG();}, 250000); // 2 Hz
        break;
    case BBQ::ErrorCode::NO_TEMP_RESPONSE:
        std::cout<<"No Temp Response!"<<std::endl;
        // timerMotorSelectLed.begin([]() {bbq.toggleLEDG();}, 125000); // 4 Hz
        break;
    default:
        // timerMotorSelectLed.end(); // stop blinking
        break;
    }

};

BBQFSM::BBQstate BBQFSM::PowerUP(){

	current_state = POWER_UP;

	// start serial port
	// Serial.begin(115200);
  // Serial.setTimeout(100);

  printCurrentState();
  usleep(delay_time);
  return AUTO_INIT; // next state to transion to

};
BBQFSM::BBQstate BBQFSM::Idle(){
  current_state = IDLE;
  printCurrentState();
  usleep(delay_time);
  return current_state;
};
BBQFSM::BBQstate BBQFSM::AutoInit(){

  if (count == 0) {
    std::cout<<"\n********************************"<<std::endl;
    std::cout<<"Initializing BBQ Control Board"<<std::endl;
    std::cout<<"Firmware Version ";
    std::cout<<BBQ_VERSION<<std::endl;
    std::cout<<"********************************\n"<<std::endl;
  }
  // Load temp waveform
  // Initialize logging
  // Set AutoControl() if successful
  count++;
  if (count > 100) {
    current_state = IDLE;
    count = 0;
  } else {
    current_state = AUTO_INIT;
  }

  printCurrentState();
  std::cout<<"count: "<<count<<std::endl;
  usleep(delay_time);
  return current_state; // next state
};

BBQFSM::BBQstate BBQFSM::AutoControl(){
  // if currentTime < finalTime{
  //    stepFanPID();
  // if controlFinished = true; next_state = AUTO_IDLE
  current_state = AUTO_CONTROL;
  printCurrentState();
  usleep(delay_time);
  return current_state;
};
BBQFSM::BBQstate BBQFSM::stepStateMachine(BBQstate stateNext){

  switch (stateNext)
  {
  case POWER_UP:
    return PowerUP();

  case IDLE:
    return Idle();

    case AUTO_INIT:
    return AutoInit();

  case AUTO_CONTROL:
    return AutoControl();

  default:
    // Serial.println("Error: Unrecognized State");
    std::cout<<"Error: Unrecognized State"<<std::endl;
        while (1) {
            // blink at 0.5 Hz
            bbq.toggleLEDG();
            // delay(1000);
        }
  }

};















// #endif // !BBQFSM_H
