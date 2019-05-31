
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
	if (dataAvailable() > 0) {
		// [TODO] Convert to bytes for final version.
		String receivedPositionX = serial.readStringUntil(',');
		String receivedPositionY = serial.readStringUntil('\r\n');
		drawManager.addPixel(receivedPositionX.toInt(), receivedPositionY.toInt());
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
