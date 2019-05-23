/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : DrawingManager.cpp
 *  Description   : Handles controling draw head to draw on whiteboard.
 */

#include "DrawingManager.hpp"

/*
 * Constructor.
 */
DrawingManager::DrawingManager(DrawHead & drawHead): drawHead(drawHead) {
}

/*
 * Destructor.
 */
DrawingManager::~DrawingManager() {
}

/*
 * Initialize drawing manager.
 */
bool DrawingManager::initialize() {
	return true;
}

/*
 * Processing loop.
 * ----
 * Moves draw head to position at front of queue.
 */
void DrawingManager::runTasks() {
	// Check if draw head is currently moving.
	if (!drawHead.isMoving()) {
		// Draw head is stationary.
		// Check if drawing head is not empty.
		if (drawQueue.size() > 0) {
			// Get next point from queue.
			std::pair<int, int> nextPoint = drawQueue.front();
			drawQueue.pop();

			// Check if dummy point.
			// Dummy points are points containing a negative
			// x or y point, used to signal to drawing manager
			// various actions to take.
			// As of now the following dummy points exist:
			// 	1. X=-1 : Begin drawing.
			// 		Push marker against board.
			// 	2. X=-2 : End drawing.
			// 		Lift marker from board.
			if (nextPoint.first < 0 || nextPoint.second < 0) {
				// Read signal.
				if (nextPoint.first == -1) {
					// TODO Begin drawing.
				} else {
					// TODO Stop drawing.
				}
			} else {
				// Move head to new point.
				drawHead.move(nextPoint.first, nextPoint.second);
			}
		}
	}
}
