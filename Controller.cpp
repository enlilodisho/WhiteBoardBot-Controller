/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : Controller.cpp
 *  Description   : Runs all modules when controller starts up.
 */
// WARNING! DO NOT ADD ANY DELAYS IN THIS FILE.
// DOING SO COULD BLOCK EXECUTION OR CAUSE MODULE FAILURES.

#include "Controller.h"
#include "config.h"
#include "Module.h"
#include "LedBlinkerModule.h"

Module * modules[NUM_STARTUP_MODULES];

void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(SERIAL_RATE);
  #endif /* DEBUG_MODE */

  // [TODO] load all modules from config
  LedBlinkerModule * ledBlinker = new LedBlinkerModule();
  modules[0] = ledBlinker;

  // Initialize all modules.
  for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
    modules[i]->initialize();
  }
}

void loop() {
  // Run all modules.
  for (unsigned int i = 0; i < NUM_STARTUP_MODULES; i++) {
    modules[i]->runTasks();
  }
}
