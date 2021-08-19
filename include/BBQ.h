/*=========================================================================//
  BBQ Class
//=========================================================================*/

// #include <ArduinoSTL.h> // this contains a <vector> class
#pragma once
#include <Eigen/Dense>
#include "BBQpins.h"
#include "Timer.h"
// #include "MAX6675.h"
#include <string>

class BBQ
{
  public:
      BBQpins pins;           // Teensy/Arduino pin definitions for BBQ

      double dt = 1/50.0;       // control loop rate
      double last_e = 0.0;
      // MAX6675 probe1;
      // MAX6675 probe2;

      double temp_probe1 = 0.0;
      double temp_probe2 = 0.0;

      double des_temp = 0.0;
      Eigen::Matrix<double,10,1> tempTraj = Eigen::MatrixXd::Zero(10,1);

      double time1 = 100.0;
      Timer timer1(double time1);

      bool fan_on = false;

      double loop_rate = 1/dt;
      Timer control_timer(double dt);

      std::string meat_type;
      std::string meat_cut;

      Eigen::Matrix<double,3,1> current_button_state;

      BBQ();
      BBQ(BBQpins pins_c);
      bool init(); // initializes modules; returns number of detected modules or -1 if errors (unless ignoreErrors = true)

      enum class ErrorCode { NO_ERROR, OVER_TEMP, LOW_FUEL, NO_TEMP_RESPONSE };
      ErrorCode getErrorCode() { return errorCode_; }; // returns any current error code

      void stepPid(double des_temp, double curr_temp); // PID controller performs one step (reads temp, computes effort, updates fan)
      void restartPid(); // reset all PID controllers

      void setLEDG(uint8_t position, bool state);               // sets green LED
      void setLEDG(bool state);                                 // sets all green LEDs
      void toggleLEDG();                                        // toggles all green LEDs together (syncs based on state of LEDG_[0])

      Eigen::Matrix<double,3,1> readButtons();   // check momentary buttons for key presses
      bool isDownPressed() { return pins.buttonStates[0]; };
      bool isUpPressed()   { return pins.buttonStates[1]; };
      bool isMenuPressed() { return pins.buttonStates[2]; };

      void displayStatusLCD();

  private:

      ErrorCode errorCode_ = ErrorCode::NO_ERROR;
      Eigen::Matrix<double,3,1> LEDG_ = { 0, 0, 0 }; // Green LED status (true = on)

};

BBQ::BBQ() {};
BBQ::BBQ(BBQpins pins_c) {
  pins = pins_c;
};

bool BBQ::init(){
  return true;
};
void BBQ::stepPid(double des_temp, double curr_temp){
  double err = des_temp - curr_temp;
  double derr = curr_temp - last_e;
  last_e = curr_temp;

  // control law: control input to system is duration of fan on
  // TODO: make a range of duration [0-10sec]
  // TODO: duration is computed from err and derr (PD controller)
  // TODO: duration applied to fan_pin -- do we wait or keep spinning?

};
void BBQ::restartPid(){};
void BBQ::setLEDG(uint8_t position, bool state){};
void BBQ::setLEDG(bool state){};
void BBQ::toggleLEDG(){};

Eigen::Matrix<double,3,1> BBQ::readButtons(){

  // digitalRead each of the buttons and put into currentButtonState
  current_button_state << 0.0, 0.0, 0.0;
  return current_button_state;
};

void BBQ::displayStatusLCD(){};
