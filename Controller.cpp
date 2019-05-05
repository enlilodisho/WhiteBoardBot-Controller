/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : Controller.cpp
 *  Description   : Runs all startup modules when controller starts up.
 */
// WARNING! DO NOT ADD ANY DELAYS IN THIS FILE.
// DOING SO COULD BLOCK EXECUTION OR CAUSE MODULE FAILURES.

#include "Controller.hpp"
#include "Protothreading.hpp"
#include "config.hpp"
#include "LedBlinkerModule.hpp"
#include "MotorDriver.hpp"

LedBlinkerModule * ledBlinker;
MotorDriver * motorDriver;
void setup() {
#ifdef DEBUG_MODE
	Serial.begin(SERIAL_RATE);
#endif /* DEBUG_MODE */

	// Initialize all modules.
	/*for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
	  STARTUP_MODULES[i]->initialize();
	  }*/
	ledBlinker = new LedBlinkerModule();
	ledBlinker->initialize();
	motorDriver = new MotorDriver(PA8, PB15, PB14, PB13, PB12);
	motorDriver->initialize();
	motorDriver->stepMotor(200);
}

void loop() {
	// Update paused modules.
	Protothreading::checkOnPausedModules();

	// Run all modules.
	/*for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
	  STARTUP_MODULES[i]->run();
	  }*/
	ledBlinker->run();
	motorDriver->run();
}
