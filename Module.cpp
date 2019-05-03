/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : Module.cpp
 *  Description   : Abstract class for modules.
 */

#include "Module.hpp"

/*
 * Constructor
 */
Module::Module() {
	paused = false;
}

/*
 * Destructor (virtual)
 * May be overridden by derived class.
 */
Module::~Module() {
	paused = true;
}

/*
 * Main loop called by Controller.
 */
void Module::run() {
	if (paused) {
		return;
	}
	runTasks();
}

/*
 * Pauses processing loop.
 * Returns true if paused.
 * Returns false if processing loop was already paused.
 */
bool Module::pause() {
	if (paused) {
		return false;
	}
	paused = true;
	return true;
}

/*
 * Resumes processing loop.
 * Returns true if resumed.
 * Returns false if processing loop was already running.
 */
bool Module::unPause() {
	if (!paused) {
		return false;
	}
	paused = false;
	return true;
}
