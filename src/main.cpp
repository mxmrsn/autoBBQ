#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <signal.h>
#include <cstdlib>

#include "BBQ.h"
#include "BBQFSM.h"
#include "BBQpins.h"

template<typename M>
M load_csv(const std::string &path) {
	std::ifstream indata;
	indata.open(path);
	std::string line;
	std::vector<double> values;
	uint rows = 0;
	while (std::getline(indata, line)) {
		std::stringstream lineStream(line);
		std::string cell;
		while (std::getline(lineStream, cell, ',')) {
			values.push_back(std::stod(cell));
		}
		++ rows;
	}
	return Eigen::Map<const Eigen::Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, Eigen::RowMajor>>(values.data(), rows, values.size()/rows);
}

BBQpins pins;                   // bbq pins connectivity
BBQ bbq(pins);                  // bbq object
BBQFSM fsm(bbq);                // finite state machine object
BBQFSM::BBQstate next_state;    // next state

bool LOG_DATA_ON = true;
std::ofstream log_file;

void setup()
{
	if (LOG_DATA_ON) {
		std::string prefix = "/Users/maxwellemerson/Documents/Arduino/autoBBQ/logs/";
		std::string file_name_note = "prediction_log.txt";

	  time_t currrent_DateTime;
    time(&currrent_DateTime);
	  log_file.precision(15);
	  log_file.open(prefix+file_name_note, std::ofstream::out | std::ofstream::app);

	  log_file<<"Experiment Date & Time, "<<"current_state";
	  log_file<<std::endl;
	}
  next_state = fsm.stepStateMachine(BBQFSM::POWER_UP); // initialize BBQ finite state machine
}

//----------------------------------------------------------------//

void loop()
{
  next_state = fsm.stepStateMachine(next_state); // switch on state
}

void signal_callback_handler(int signum) {
   std::cout << "Caught signal " << signum << std::endl;
   if(LOG_DATA_ON && log_file.is_open()) { log_file.close(); }
   // Terminate program
   exit(signum);
}

int main () {

  setup();

  signal(SIGINT, signal_callback_handler); // handle ctrl+c program end
  while(1) {
    loop();
    if (LOG_DATA_ON) {

      time_t currrent_DateTime;
      time(&currrent_DateTime);
      log_file<<ctime(&currrent_DateTime)<<","<<fsm.current_state<<",";
      // log_file<<fsm.bbq.button_state<<",";
      // log_file<<fsm.temp_probe1<<",";
      // log_file<<fsm.temp_probe2<<",";
  		log_file<<std::endl;
  	}
  }

	return EXIT_SUCCESS;
}
