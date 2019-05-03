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

void setup() {
#ifdef DEBUG_MODE
	Serial.begin(SERIAL_RATE);
#endif /* DEBUG_MODE */

	// Initialize all modules.
	for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
		STARTUP_MODULES[i]->initialize();
	}
}

void loop() {
	// Update paused modules.
	Protothreading::checkOnPausedModules();

	// Run all modules.
	for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
		STARTUP_MODULES[i]->run();
	}
}
