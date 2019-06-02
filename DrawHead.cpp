/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : DrawHead.cpp
 *  Description   : The mechanism that draws onto the whiteboard.
 */

#include "Arduino.h"
#include "config.hpp"
#include "DrawHead.hpp"

const unsigned int POS_SERVO_DRAWING = 0;
const unsigned int POS_SERVO_NOTDRAWING = 45;

/*
 * Constructor.
 */
DrawHead::DrawHead(const MotorDriverPins & xMotorPins,
		const MotorDriverPins & yMotorPins, Servo * drawServo):
	drawServo(drawServo) {
	// Create Motor Driver module for each motor.
	xMotor = new MotorDriver(xMotorPins.enable, xMotorPins.reset,
			xMotorPins.sleep, xMotorPins.step, xMotorPins.dir);
	yMotor = new MotorDriver(yMotorPins.enable, yMotorPins.reset,
			yMotorPins.sleep, yMotorPins.step, yMotorPins.dir);

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
	// Move marker servo to 90 degrees.
	stopDrawing();
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
	int deltaPos;

	// Check if x-axis needs to be moved first.
	if (desiredX != currPos[0]) {
		deltaPos = desiredX - currPos[0];
		if (desiredX > currPos[0]) {
			// Need to move DrawHead to the right.
			xMotor->setDirection(MotorDriver::FORWARD);
		} else if (desiredX < currPos[0]) {
			// Need to move DrawHead to the left.
			xMotor->setDirection(MotorDriver::REVERSE);
		}
		if (!xMotor->stepMotor(abs(deltaPos) * MOTOR_X_STEPS_MM, this,
					updateMoveStatus)) {
			// Failure, abort moving.
			Serial.println("ERROR! Failed to move x-axis motor. \
					Aborted move request.");
			moveStatus = 0;
			return false;
		} else {
			_currPos[0] += deltaPos;
		}
	} else {
		// Draw head already at the correct horizontal position.
		updateMoveStatus(this);
	}

	// Check if y-axis needs to be moved.
	if (desiredY != currPos[1]) {
		deltaPos = desiredY - currPos[1];
		if (desiredY > currPos[1]) {
			// Need to move DrawHead down.
			yMotor->setDirection(MotorDriver::CLOCKWISE);
		} else if (desiredY < currPos[1]) {
			// Need to move DrawHead up.
			yMotor->setDirection(MotorDriver::COUNTERCLOCKWISE);
		}
		if (!yMotor->stepMotor(abs(deltaPos) * MOTOR_Y_STEPS_MM, this,
					updateMoveStatus)) {
			// Failure to move y, but request for moving x succeeded.
			updateMoveStatus(this);
			Serial.println("ERROR! Failed to move y motor, while x \
					motor succeeded.");
		} else {
			_currPos[1] += deltaPos;
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
	return true;
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
 * Push marker against board.
 */
void DrawHead::startDrawing() {
	drawServo->write(0);
}

/*
 * Release marker from board.
 */
void DrawHead::stopDrawing() {
	drawServo->write(45);
}

/*
 * Calibrate draw head position.
 * Detects the size of the whiteboard.
 */
void DrawHead::calibrate() {
	// [TODO] Move draw head to home position (0,0).
	// Idea: Have sensors on top left and right edges to detect when drawing
	// mechanism is at home position.
	// For now, just assume that the robot always starts at 0,0.
	_currPos[0] = 0;
	_currPos[1] = 0;
}
