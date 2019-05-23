#ifndef DRAWING_MANAGER_H
#define DRAWING_MANAGER_H

#include <queue>
#include "DrawHead.hpp"
#include "Module.hpp"

class DrawingManager: public Module {

	public:    
		// Constructor.
		DrawingManager(DrawHead & drawHead);
		// Destructor.
		~DrawingManager();

		// Implement abstract methods.
		bool initialize();
		void runTasks();
	
	private:
		DrawHead & drawHead;
		std::queue<std::pair<int, int>> drawQueue;

};

#endif /* DRAWING_MANAGER_H */
