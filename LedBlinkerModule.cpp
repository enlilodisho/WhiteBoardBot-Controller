/** Project       : White Board Bot Controller
    ----------------------------------------------------------
    File          : LedBlinkerModule.cpp
    Description   : Temporarily led blinker module for testing modules.
*/

#include "Arduino.h"
#include "LedBlinkerModule.h"
#include "Protothreading.h"

// Destructor
LedBlinkerModule::~LedBlinkerModule() {
  
}

bool LedBlinkerModule::initialize() {
  pinMode(PC13, OUTPUT);
  timer1 = Protothreading::timer(250);
  timer2 = Protothreading::timer(250);
  return true;
}

void LedBlinkerModule::runTasks() {
  if (Protothreading::timerCheckAndSave(timer1)) {
    digitalWrite(PC13, LOW);
    Protothreading::timerReset(timer2);
  } else if (Protothreading::timerCheckAndSave(timer2)) {
    digitalWrite(PC13, HIGH);
    Protothreading::timerReset(timer1);
  }
}
