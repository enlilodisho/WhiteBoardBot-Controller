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
	drawQueue = new DataQueue<Point>(100);
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
		if (drawQueue->item_count() > 0) {
			// Get next point from queue and remove it.
			Point nextPoint = drawQueue->dequeue();

			// Check if dummy point.
			// Dummy points are points containing a negative
			// x or y point, used to signal to drawing manager
			// various actions to take.
			// As of now the following dummy points exist:
			// 	1. X=-1 : Begin drawing.
			// 		Push marker against board.
			// 	2. X=-2 : End drawing.
			// 		Lift marker from board.
			if (nextPoint.x < 0 || nextPoint.y < 0) {
				// Read signal.
				if (nextPoint.x == -1) {
					// Begin drawing.
					drawHead.startDrawing();
				} else {
					// Stop drawing.
					drawHead.stopDrawing();
				}
			} else {
				// Move head to new point.
				drawHead.move(nextPoint.x, nextPoint.y);
			}
		}
	}
}

/*
 * Adds a pixel to draw to the queue.
 */
void DrawingManager::addPixel(unsigned int x, unsigned int y) {
	Point last = drawQueue->back();
	// TODO calculate distance between new pixel and last pixel.
	// If distance great enough, add stop drawing dummy point, pixel point,
	// 			   then add start drawing dummy point to queue.
	// Otherwise, just add pixel point to queue.
	drawQueue->enqueue((Point){x,y});
}
