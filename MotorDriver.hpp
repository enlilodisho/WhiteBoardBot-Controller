#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Module.hpp"

class MotorDriver: public Module {

	public:
		MotorDriver(uint penable, uint preset, uint psleep, uint pstep, uint pdir);

		~MotorDriver();

		bool initialize();
		void runTasks();

		void setDirection(const int & direction);
		bool stepMotor();

		// Power management
		void suspend();
		void wakeUp();
		void enable();
		void disable();

	protected:
		const int pinEnable, pinReset, pinSleep, pinStep, pinDir;

		static void stepMotor(Module * module);

	private:
		int stepping = 0;

};

#endif /* MOTOR_DRIVER_H */
