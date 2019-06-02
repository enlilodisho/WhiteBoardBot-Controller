#ifndef DRAW_HEAD_H
#define DRAW_HEAD_H

#include <Servo.h>
#include "Module.hpp"
#include "MotorDriver.hpp"

class DrawHead: public Module {

	public:
		// Constructor
		DrawHead(const struct MotorDriverPins & xMotorPins,
				const struct MotorDriverPins & yMotorPins,
				Servo * drawServo);
		// Destructor
		~DrawHead();

		// Implement abstract methods.
		bool initialize();
		void runTasks();

		const unsigned int * currPos = _currPos;

		bool move(unsigned int desiredX, unsigned int desiredY);
		bool move(unsigned int desiredX, unsigned int desiredY,
				Module* callbackModule, void(*callback)(Module*));
		bool isMoving();

		void startDrawing();
		void stopDrawing();

	protected:
		MotorDriver * xMotor;
		MotorDriver * yMotor;

		// Gets whiteboard size, then moves DrawHead to (0,0).
		void calibrate();

	private:
		unsigned int _currPos[2];

		unsigned int moveStatus;
		std::pair<Module*, void(*)(Module*)> moveCallback;
		static void updateMoveStatus(Module * module);

		Servo * drawServo;
		const static unsigned int POS_SERVO_DRAWING;
		const static unsigned int POS_SERVO_NOTDRAWING;

};

struct MotorDriverPins {
	unsigned int enable;
	unsigned int reset;
	unsigned int sleep;
	unsigned int step;
	unsigned int dir;
};

#endif /* DRAW_HEAD_H */
