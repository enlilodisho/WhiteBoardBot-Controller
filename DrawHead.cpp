/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : DrawHead.cpp
 *  Description   : The mechanism that draws onto the whiteboard.
 */

#include "Arduino.h"
#include "DrawHead.hpp"
#include <cmath> // std::abs

/*
 * Constructor.
 */
DrawHead::DrawHead(MotorDriverPins * xMotorPins, MotorDriverPins * yMotorPins) {
	// Create Motor Driver module for each motor.
	xMotor = new MotorDriver(xMotorPins->enable, xMotorPins->reset,
			xMotorPins->sleep, xMotorPins->step, xMotorPins->dir);
	yMotor = new MotorDriver(yMotorPins->enable, yMotorPins->reset,
			yMotorPins->sleep, yMotorPins->step, yMotorPins->dir);

	moveStatus = 0;
	moveCallback.first = nullptr;
	moveCallback.second = nullptr;
}

/*
 * Destructor.
 */
DrawHead::~DrawHead() {
}

/*
 * Initialize draw head.
 */
bool DrawHead::initialize() {
	// Initialize motor drivers. (powers on motors)
	xMotor->initialize();
	yMotor->initialize();
	calibrate();
	return true;
}

/*
 * Processing loop.
 */
void DrawHead::runTasks() {
	// Update motors position, if necessary.
	xMotor->run();
	yMotor->run();
}

/*
 * Move the DrawHead to a specific position.
 * Returns true if move requested.
 * Returns false if already moving from prior request.
 */
bool DrawHead::move(unsigned int desiredX, unsigned int desiredY) {
	if (moveStatus != 0) {
		return false;
	}
	moveStatus = 1;
	unsigned int deltaPos;

	// Check if x-axis needs to be moved first.
	if (desiredX != currPos[0]) {
		if (desiredX > currPos[0]) {
			// Need to move DrawHead to the right.
			xMotor->setDirection(MotorDriver::FORWARD);
		} else if (desiredX < currPos[0]) {
			// Need to move DrawHead to the left.
			xMotor->setDirection(MotorDriver::REVERSE);
		}
		deltaPos = (desiredX > currPos[0]) ? (desiredX - currPos[0])
			: (currPos[0] - desiredX);
		if (!xMotor->stepMotor(deltaPos, this, updateMoveStatus)) {
			// Failure, abort moving.
			Serial.println("ERROR! Failed to move x-axis motor. \
					Aborted move request.");
			moveStatus = 0;
			return false;
		} else {
			_currPos[0] += desiredX;
		}
	} else {
		// Draw head already at the correct horizontal position.
		updateMoveStatus(this);
	}

	// Check if y-axis needs to be moved.
	if (desiredY != currPos[1]) {
		if (desiredY > currPos[1]) {
			// Need to move DrawHead down.
			yMotor->setDirection(MotorDriver::CLOCKWISE);
		} else if (desiredY < currPos[1]) {
			// Need to move DrawHead up.
			yMotor->setDirection(MotorDriver::COUNTERCLOCKWISE);
		}
		deltaPos = std::abs(desiredY - currPos[1]);
		if (!yMotor->stepMotor(deltaPos, this, updateMoveStatus)) {
			// Failure to move y, but request for moving x succeeded.
			updateMoveStatus(this);
			Serial.println("ERROR! Failed to move y motor, while x motor \
					succeeded.");
		} else {
			_currPos[1] += desiredY;
		}
	} else {
		// Draw head already at the correct vertical position.
		updateMoveStatus(this);
	}

	return true;
}

/*
 * Move the DrawHead to a specific position.
 * Returns true if move requested and invokes callback when move finished.
 * Returns false if already moving from prior request.
 */
bool DrawHead::move(unsigned int desiredX, unsigned int desiredY,
		Module* callbackModule, void(*callback)(Module*)) {
	if (!move(desiredX, desiredY)) {
		return false;
	}
	moveCallback.first = callbackModule;
	moveCallback.second = callback;
}

/*
 * Update move status.
 */
void DrawHead::updateMoveStatus(Module * module) {
	DrawHead * drawHead = (DrawHead*)module;
	drawHead->moveStatus++;
	// Check if finished moving both axis motors.
	if (drawHead->moveStatus >= 3) {
		drawHead->moveStatus = 0;
		// Check if module has callback.
		if (drawHead->moveCallback.second != nullptr) {
			// Module has callback.
			auto callback = drawHead->moveCallback.second;
			auto callbackModule = drawHead->moveCallback.first;
			// Reset move callback.
			drawHead->moveCallback.first = nullptr;
			drawHead->moveCallback.second = nullptr;
			// Invoke callback.
			callback(callbackModule);
		}
	}
}

/*
 * Returns true when x and/or y axis motor is moving.
 */
bool DrawHead::isMoving() {
	if (moveStatus != 0) {
		return true;
	}
	return false;
}

/*
 * Calibrate draw head position.
 * Detects the size of the whiteboard.
 */
void DrawHead::calibrate() {
	// Move draw head to home position (0,0).
	_currPos[0] = 0;
	_currPos[1] = 0;
}
