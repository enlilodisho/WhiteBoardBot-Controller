/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : config.h
 *  Description   : Contains settings that can be adjusted.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "LedBlinkerModule.h"

// Uncomment line below to enable Serial debug messages.
#define DEBUG_MODE
// Serial Baud Rate
#define SERIAL_RATE 115200

// Modules allow us to emulate multithreading (we're actually doing protothreading).
// Startup modules are started by the Controller on startup. These modules are
// highest priority as they are being updated as fast as possible.
// Also note that adding more startup modules will slow down all other modules.
#define NUM_STARTUP_MODULES 1
LedBlinkerModule * const ledBlinker = new LedBlinkerModule;
Module * const STARTUP_MODULES[NUM_STARTUP_MODULES] = { ledBlinker };



#endif /* CONFIG_H */
