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
#include "Module.hpp"
// Include all startup modules below:
#include "LedBlinkerModule.hpp"

// Add pointers to startup modules in array below.
Module* startupModules[] = {new LedBlinkerModule()};

// Get number of startup modules.
const size_t NUM_STARTUP_MODULES = (sizeof startupModules /
		sizeof startupModules[0]);

void setup() {
#ifdef DEBUG_MODE
	Serial.begin(SERIAL_RATE);
#endif /* DEBUG_MODE */

	// Initialize all startup modules.
	for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
		startupModules[i]->initialize();
	}
}

void loop() {
	// Update paused modules.
	Protothreading::checkOnPausedModules();

	// Run all modules.
	for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
		startupModules[i]->run();
	}
}
