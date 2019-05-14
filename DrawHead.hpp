#ifndef DRAW_HEAD_H
#define DRAW_HEAD_H

#include "Module.hpp"
#include "MotorDriver.hpp"

class DrawHead: public Module {

	public:
		// Constructor
		// TODO Include mechanism for pressing marker against board.
		DrawHead(struct MotorDriverPins * xMotorPins, struct MotorDriverPins * yMotorPins);
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

};

struct MotorDriverPins {
	unsigned int enable;
	unsigned int reset;
	unsigned int sleep;
	unsigned int step;
	unsigned int dir;
};

#endif /* DRAW_HEAD_H */
