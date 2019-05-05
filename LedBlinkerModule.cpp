/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : LedBlinkerModule.cpp
 *  Description   : Temporarily led blinker module for testing modules.
 */

#include "Arduino.h"
#include "LedBlinkerModule.hpp"
#include "Protothreading.hpp"

// Destructor
LedBlinkerModule::~LedBlinkerModule() {

}

bool LedBlinkerModule::initialize() {
	pinMode(PC13, OUTPUT);
	ledPinHigh = false;
	return true;
}

void LedBlinkerModule::runTasks() {
	Protothreading::pause(this, 1000, toggleLed);
}

void LedBlinkerModule::toggleLed(Module * module) {
  if (((LedBlinkerModule*)module)->ledPinHigh) {
      digitalWrite(PC13, LOW);
      ((LedBlinkerModule*)module)->ledPinHigh = false;
    } else {
      digitalWrite(PC13, HIGH);
      ((LedBlinkerModule*)module)->ledPinHigh = true;
    }
}
