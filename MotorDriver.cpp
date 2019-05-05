/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : MotorDriver.cpp
 *  Description   : Controls motor drivers.
 */

#include "Arduino.h"
#include "MotorDriver.hpp"
#include "Protothreading.hpp"

const static int CLOCKWISE = 1;
const static int COUNTERCLOCKWISE = 2;
const static int FORWARD = CLOCKWISE;
const static int REVERSE = COUNTERCLOCKWISE;

/*
 * Constructor.
 */
MotorDriver::MotorDriver(uint penable, uint preset, uint psleep, uint pstep,
		uint pdir): pinEnable(penable), pinReset(preset), pinSleep(psleep),
		pinStep(pstep), pinDir(pdir) {
	// Turn off driver.
	suspend();
	// Enable sensor FET outputs
	enable();
	// Bring driver out of reset state.
	pinMode(pinReset, INPUT_PULLUP);
	// Set motor direction to clockwise.
	setDirection(CLOCKWISE);
	// Initialize step pin to low.
	pinMode(pinStep, INPUT_PULLDOWN);
	}

/*
 * Destructor.
 */
MotorDriver::~MotorDriver() {
}

/*
 * Initialize sensor.
 */
bool MotorDriver::initialize() {
	// Wake up driver.
	wakeUp();
	return true;
}

/*
 * Processing loop.
 */
void MotorDriver::runTasks() {

}

/*
 * Steps motor once.
 * Returns true if stepping.
 * Returns false if already stepping from another request.
 */
bool MotorDriver::stepMotor() {
	if (stepping != 0) {
		return false;
	}
	stepMotor(this);
	return true;
}

/*
 * Step motor once.
 * Sends 1 ms pulse on step pin.
 * Pauses MotorDriver from processing other tasks for ~2ms.
 */
void MotorDriver::stepMotor(Module * module) {
	MotorDriver * driver = (MotorDriver*)module;
	switch (driver->stepping) {

		case 0: // Pullup step pin.
			driver->stepping = 1;
			pinMode(driver->pinStep, INPUT_PULLUP);
			// Wait 1ms.
			Protothreading::pause(module, 1, stepMotor);
			return;

		case 1: // Puldown step pin.
			pinMode(driver->pinStep, INPUT_PULLDOWN);
			driver->stepping = 2;
			// 1ms stepping cooldown.
			Protothreading::pause(module, 1, stepMotor);
			return;

		case 2: // Enable stepping again.
			driver->stepping = 0;
			return;
	}
}

/*
 * Set the direction of the motor.
 */
void MotorDriver::setDirection(const int & direction) {
	if (direction == CLOCKWISE) {
		pinMode(pinDir, INPUT_PULLDOWN);
	} else if (direction == COUNTERCLOCKWISE) {
		pinMode(pinDir, INPUT_PULLUP);
	}
}


/////////////////////////////////////////////////
// Driver power control functions below.

/*
 * Minimizes power consumption by turning off FET outputs
 * and most of the logic on the motor driver.
 */
void MotorDriver::suspend() {
	// Put driver in sleep mode.
	pinMode(pinSleep, INPUT_PULLDOWN);
}

/*
 * Brings driver out of sleep mode.
 */
void MotorDriver::wakeUp() {
	pinMode(pinSleep, INPUT_PULLUP);
}

/*
 * Enable driver FET outputs.
 * Holds motor position.
 */
void MotorDriver::enable() {
	pinMode(pinEnable, INPUT_PULLDOWN);
}

/*
 * Disable driver FET outputs.
 * Frees up motor position.
 */
void MotorDriver::disable() {
	pinMode(pinEnable, INPUT_PULLUP);
}
