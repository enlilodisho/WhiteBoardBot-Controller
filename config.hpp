/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : config.h
 *  Description   : Contains settings that can be adjusted.
 */

#ifndef CONFIG_H
#define CONFIG_H

// Uncomment line below to enable Serial debug messages.
#define DEBUG_MODE
// Serial Baud Rate
#define SERIAL_RATE 115200


/* Draw Head Motors Config */
// X-Axis Motor //
// Pins
#define PIN_MOTOR_X_SLEEP	PA0
#define PIN_MOTOR_X_ENABLE	PA1
#define PIN_MOTOR_X_RESET	PA2
#define PIN_MOTOR_X_DIR		PA3
#define PIN_MOTOR_X_STEP	PA4
// The number of steps to travel 1 milimeter in x direction.
#define MOTOR_X_STEPS_MM	5
// Y-Axis Motor //
// Pins
#define PIN_MOTOR_Y_SLEEP	PA5
#define PIN_MOTOR_Y_ENABLE	PA6
#define PIN_MOTOR_Y_RESET	PA7
#define PIN_MOTOR_Y_DIR		PB0
#define PIN_MOTOR_Y_STEP	PB1
// The number of steps to travel 1 milimeter in y direction.
#define MOTOR_Y_STEPS_MM	5
// Draw Servo //
#define PIN_DRAW_SERVO		PA8


#endif /* CONFIG_H */
