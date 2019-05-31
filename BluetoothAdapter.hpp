#ifndef BLUETOOTH_ADAPTER_H
#define BLUETOOTH_ADAPTER_H 

#include "Arduino.h"
#include "DrawingManager.hpp"
#include "Module.hpp"

class BluetoothAdapter: public Module {
	public:
		BluetoothAdapter(HardwareSerial & serial,
				DrawingManager & drawManager);
		~BluetoothAdapter();

		bool initialize();
		void runTasks();

		int dataAvailable();
		int readByte();
		String readString();
	protected:
		HardwareSerial& serial;
		DrawingManager& drawManager;
};

#endif /* BLUETOOTH_ADAPTER_H */
