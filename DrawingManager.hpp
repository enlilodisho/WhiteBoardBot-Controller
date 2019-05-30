#ifndef DRAWING_MANAGER_H
#define DRAWING_MANAGER_H

/* Queue.h is from https://github.com/EinarArnason/ArduinoQueue
 * It has been modified to include a back() method
 * that returns the node at the back of the queue.
 */
#include <Queue.h>
#include "DrawHead.hpp"
#include "Module.hpp"

struct Point {
	int x;
	int y;
};

class DrawingManager: public Module {

	public:    
		// Constructor.
		DrawingManager(DrawHead & drawHead);
		// Destructor.
		~DrawingManager();

		// Implement abstract methods.
		bool initialize();
		void runTasks();

		// Add pixel to draw to queue.
		void addPixel(unsigned int x, unsigned int y);

	private:
		DrawHead & drawHead;
		DataQueue<Point> * drawQueue;

};

#endif /* DRAWING_MANAGER_H */
