
/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : BluetoothAdapter.cpp
 *  Description   : Reads serial data from HC-05 bluetooth adapter.
 */

#include "BluetoothAdapter.hpp"

/*
 * Constructor.
 */
BluetoothAdapter::BluetoothAdapter(HardwareSerial & serial,
		DrawingManager & drawManager): serial(serial),
		drawManager(drawManager) {
}

/*
 * Destructor.
 */
BluetoothAdapter::~BluetoothAdapter() {
}

/*
 * Initialize bluetooth adapter.
 */
bool BluetoothAdapter::initialize() {
	serial.begin(115200);
	return true;
}

/*
 * Processing loop.
 */
void BluetoothAdapter::runTasks() {
	// If two integers are available to read.
	if (dataAvailable() >= 2*sizeof(int)) {
		// Read x position.
		int receivedPositionX = 0;
		for (int i = 0; i < sizeof(int); i++) {
			receivedPositionX <<= 8; // shift 8 bits
			receivedPositionX |= serial.read(); // OR in one byte.
		}

		// Read y position.
		int receivedPositionY = 0;
		for (int i = 0; i < sizeof(int); i++) {
			receivedPositionY <<= 8; // shift 8 bits
			receivedPositionY |= serial.read(); // OR in one byte.
		}

		// Send coordinates read to DrawingManager.
		drawManager.addPixel(receivedPositionX, receivedPositionY);
	}
}

/*
 * Returns number of bytes available to read.
 */
int BluetoothAdapter::dataAvailable() {
	return serial.available();
}

/*
 * Returns byte read.
 */
int BluetoothAdapter::readByte() {
	return serial.read();
}

/*
 * Returns string read.
 */
String BluetoothAdapter::readString() {
	return serial.readString();
}
