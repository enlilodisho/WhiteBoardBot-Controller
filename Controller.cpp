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
// Include modules below:
#include "LedBlinkerModule.hpp"
#include "DrawHead.hpp"
#include "DrawingManager.hpp"
#include "MotorDriver.hpp"

// Add pointers to startup modules in array below.
Module* startupModules[] = {new LedBlinkerModule(), (DrawHead*)nullptr,
	(DrawingManager*)nullptr};

// Get number of startup modules.
const size_t NUM_STARTUP_MODULES = (sizeof startupModules /
		sizeof startupModules[0]);

void setup() {
#ifdef DEBUG_MODE
	Serial.begin(SERIAL_RATE);
#endif /* DEBUG_MODE */

	setupWhiteboardBotModules();

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

void setupWhiteboardBotModules() {
	MotorDriverPins xMotorPins;
	xMotorPins.enable	= PIN_MOTOR_X_ENABLE;
	xMotorPins.reset	= PIN_MOTOR_X_RESET;
	xMotorPins.sleep	= PIN_MOTOR_X_SLEEP;
	xMotorPins.step	= PIN_MOTOR_X_STEP;
	xMotorPins.dir		= PIN_MOTOR_X_DIR;

	MotorDriverPins yMotorPins;
	yMotorPins.enable	= PIN_MOTOR_Y_ENABLE;
	yMotorPins.reset	= PIN_MOTOR_Y_RESET;
	yMotorPins.sleep	= PIN_MOTOR_Y_SLEEP;
	yMotorPins.step	= PIN_MOTOR_Y_STEP;
	yMotorPins.dir		= PIN_MOTOR_Y_DIR;

	// Create DrawHead on stack.
	DrawHead* drawHead = new DrawHead(xMotorPins, yMotorPins);
	
	// Create DrawingManager on stack.
	DrawingManager* drawManager = new DrawingManager(*drawHead);

	// Add DrawHead to startup modules.
	startupModules[1] = drawHead;
	// Add DrawingManager to startup modules.
	startupModules[2] = drawManager;
}
