#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Module.hpp"
#include <utility>

class MotorDriver: public Module {

	public:
		MotorDriver(uint penable, uint preset, uint psleep, uint pstep, uint pdir);

		~MotorDriver();

		bool initialize();
		void runTasks();

		void setDirection(const int & direction);
		bool stepMotor(unsigned int count = 1);
		bool stepMotor(unsigned int count,
				Module* callbackModule, void(*callback)(Module*));

		// Power management
		void suspend();
		void wakeUp();
		void enable();
		void disable();

	protected:
		const int pinEnable, pinReset, pinSleep, pinStep, pinDir;

		static void stepMotor(Module * module);
		unsigned int stepCount;

	private:
		unsigned char steppingStatus;
		std::pair<Module*, void(*)(Module*)> stepCallback;

};

#endif /* MOTOR_DRIVER_H */
