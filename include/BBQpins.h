//=========================================================================//
/*
BBQpins Class
Designed for use with Teensy 3.1/3.2
This class initializes and allows easy referencing to all pins
*/
//=========================================================================//

#ifndef BBQpins_h
#define BBQpins_h

#pragma once
#include <stdint.h>

class BBQpins
{
public:
  uint8_t fan_pin = 11;
  uint8_t cs_temp_probe1 = 12;
  uint8_t cs_temp_probe2 = 13;

  uint8_t globalInhibit = 33;                                 // global enable control for all amps
  uint8_t maxNumBoards = 6;                                   // number of daughterboard sockets
  uint8_t csSdCard = 4;                                       // SD card chip-select
  uint8_t csDac = 27;                                         // global chip-select pin (SYNC) for DACs (AD5761R)
  uint8_t modeSelect = 28;                                    // connected to manual/ROS mode select switch
  uint8_t csEnc[6] = { 20, 17, 15, 29, 32, 30 };              // chip-select pins for quadrature encoder IC (LS7366R)
  uint8_t ampCtrl[6] = { 21, 16, 14, 25, 26, 31 };            // motor amp control pins (ENABLED when ampCtrl == limitSwitchState)
  uint8_t led[6] = { 24, 7, 6, 5, 3, 2 };                     // control the green LEDs
  uint8_t buttonDown = 0;
  uint8_t buttonUp = 1;
  uint8_t buttonMenu = 23;
  uint8_t buttons[3] = { buttonDown, buttonUp, buttonMenu };
  float   buttonThresh[3] = { 1200, 1200, 1200 };             // thresholds that itute a key press (pF)
  volatile bool buttonStates[3] = { 0, 0, 0 };                      // volatile in case used within interrupt

  BBQpins(){};
  void initPins();
};

void BBQpins::initPins() // initializes all SPI chip-select pins
{
  // Setup pin input/outputs
  // de-select SD card
  // pinMode(csSdCard, OUTPUT);
  // digitalWriteFast(csSdCard, HIGH);
  //
  // // CTRL switch input
  // pinMode(modeSelect, INPUT);
  //
  // // global inhibit
  // pinMode(globalInhibit, OUTPUT);
  // digitalWriteFast(globalInhibit, HIGH); // HIGH = INHIBIT

};

#endif
