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
  stepPinPulledUp = false;
}

/* Destructor */
MotorDriver::~MotorDriver() {
  
}

/* Initialize Module */
bool MotorDriver::initialize() {
  sleep();
  enable();
  pinMode(pinReset, INPUT_PULLUP);
  pinMode(pinStep, INPUT_PULLDOWN);
  setDirectionFWD();
  return true;
}

/*
 * Module Loop
 */
void MotorDriver::runTasks() {
  // Check if stepping.
  if (stepTimer >= 0 && Protothreading::timerCheckAndSave(stepTimer)) {
    if (stepPinPulledUp) {
      toggleStepPin();
      Protothreading::timerReset(stepTimer);
    } else {
      Protothreading::timerDelete(stepTimer);
      stepTimer = -1;
    }
  }
}

/*
 * Steps motor once. Returns whether step signal sent.
 */
bool MotorDriver::motorStep() {
  if (stepTimer >= 0) {
    // Already stepping.
    return false;
  }
  // Send 1ms pulse on pinStep.
  pinMode(pinStep, INPUT_PULLUP);
  stepPinPulledUp = true;
  stepTimer = Protothreading::timerMicroseconds(1000);
  return true;
}

/*
 * Helper method for motorStep.
 */
void MotorDriver::toggleStepPin() {
  if (stepPinPulledUp) {
    pinMode(pinStep, INPUT_PULLDOWN);
    stepPinPulledUp = false;
  } else {
    pinMode(pinStep, INPUT_PULLUP);
    stepPinPulledUp = true;
  }
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
