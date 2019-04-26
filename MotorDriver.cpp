/** Project       : White Board Bot Controller
    ----------------------------------------------------------
    File          : MotorDriver.cpp
    Description   : Interface for stepper motor driver.
      and controlling motor.
*/

#include "Arduino.h"
#include "MotorDriver.h"
#include "Protothreading.h"

/* Constructor */
MotorDriver::MotorDriver(int penable, int preset, int psleep, int pstep, int pdir):
  pinEnable(penable), pinReset(preset), pinSleep(psleep), pinStep(pstep), pinDirection(pdir) {
  stepTimer = -1;
}

/* Destructor */
MotorDriver::~MotorDriver() {
  
}

/* Initialize Module */
bool MotorDriver::initialize() {
  enable();
  pinMode(pinReset, INPUT_PULLUP);
  sleep();
  setDirectionFWD();
  return true;
}

/*
 * Module Loop
 */
void MotorDriver::runTasks() {
  // Check if stepping.
  if (stepTimer >= 0 && Protothreading::timerCheckAndDelete(stepTimer)) {
    pinMode(pinStep, INPUT_PULLDOWN);
    stepTimer = -1;
  }
}

/*
 * Steps motor once.
 */
void MotorDriver::motorStep() {
  if (pinStep >= 0) {
    // Already stepping.
    return;
  }
  // Send 1ms pulse on pinStep.
  pinMode(pinStep, INPUT_PULLUP);
  stepTimer = Protothreading::timerMicroseconds(1000);
}

/*
 * Brings motor driver to sleep mode.
 * Halts power consumption from sensor.
 */
void MotorDriver::sleep() {
  pinMode(pinSleep, INPUT_PULLDOWN);
}

/*
 * Brings motor driver out of sleep mode.
 */
void MotorDriver::wake() {
  pinMode(pinSleep, INPUT_PULLUP);
}

/*
 * Enable FET outputs.
 */
void MotorDriver::enable() {
  pinMode(pinEnable, INPUT_PULLDOWN);
}

/*
 * Disable FET outputs.
 */
void MotorDriver::disable() {
  pinMode(pinEnable, INPUT_PULLUP);
}

/*
 * Sets motor direction to forward.
 */
void MotorDriver::setDirectionFWD() {
  pinMode(pinDirection, INPUT_PULLUP);
}

/*
 * Sets motor direction to reverse.
 */
void MotorDriver::setDirectionREV() {
  pinMode(pinDirection, INPUT_PULLDOWN);
}
