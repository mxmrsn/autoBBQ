/*=========================================================================//
Timer.h
Implements a timer object for the AutoBBQ
Designed for use with Teensy 3.1/3.2
//=========================================================================*/

#ifndef TIMER_H
#define TIMER_H

class Timer {

  public:
    double loop_period = 100;                    // 100 ms (0.1 sec) -- default
    double loop_rate = 1/loop_period;            // 10 hz

    double curr_time = 0.0;
    double start_time = 0.0;

    Timer(double duration){loop_period=duration;}; // construct with time duration (period)
    bool startTimer();
    bool checkTimer();
  private:

};

bool Timer::startTimer() {
  // start_time = millis();
  return true;
};

bool Timer::checkTimer() {
  // curr_time = millis();
  if ( (curr_time - start_time) > loop_period ) {
    // duration finished
    return true;
  } else {
    // within duration
    return false;
  }
};

#endif // !TIMER_H
