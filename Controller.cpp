/* WhiteBoardBot-Controller.ino
 * Contains base code responsible for starting and running modules.
 * -------------------------------
 * WARNING: DO NOT ADD ANY DELAYS IN THIS FILE.
 * Only use this base code to run modules.
 * Have everything else in the module class.
 */
#include "Controller.h"
#include "config.h"

void setup() {
  #ifdef DEBUG_MODE
    Serial.begin(SERIAL_RATE);
  #endif /* DEBUG_MODE */

  
}

void loop() {
  
}
