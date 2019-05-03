/** Project       : White Board Bot Controller
 *  ----------------------------------------------------------
 *  File          : Protothreading.cpp
 *  Description   : "Static" class containing useful methods for protothreading.
 */

#include "Arduino.h"
#include "Protothreading.hpp"

/*
 * Paused modules data. (map)
 * Key: Module*
 * Value: Pair <pauseDuration, pausedSince>
 */
std::map<Module *, std::pair<unsigned long, unsigned long>>
Protothreading::pausedModules;

/*
 * Modules callback data. (map)
 * Key: Module*
 * Value: Callback to invoke when module resumes.
 */
std::map<Module *, std::function<void()>> Protothreading::callbacks;

/*
 * Pause module for a specific duration in miliseconds.
 */
bool Protothreading::pause(Module * module, unsigned long ms) {
	return pauseMicros(module, ms*1000);
}

/*
 * Pause module for a specific duration in microseconds.
 */
bool Protothreading::pauseMicros(Module * module, unsigned long us) {
	// Check if already paused.
	if (!module->pause()) {
		return false;
	}

	trackPausedModule(module, us);
	return true;
}

/*
 * Pause module for a specific duration in miliseconds.
 * Call callback when module resumes.
 */
bool Protothreading::pause(Module * module, unsigned long ms,
		std::function<void()> callback) {
	return pauseMicros(module, ms, callback);
}

/*
 * Pause module for a specific duration in microseconds.
 * Call callback when module resumes.
 */
bool Protothreading::pauseMicros(Module * module, unsigned long us,
		std::function<void()> callback) {
	if (!pauseMicros(module, us)) {
		return false;
	}
	addCallback(module, callback);
	return true;
}

/*
 * Checks on all paused modules and resumes them if necessary.
 */
void Protothreading::checkOnPausedModules() {
	// Get current time.
	unsigned long curTime = micros();

	// Loop through all paused modules and check if duration passed.
	auto it = pausedModules.begin();
	while (it != pausedModules.end()) {
		if (curTime - (it->second).second < (it->second).first) {
			it++;
			continue;
		}

		// Duration has passed, unpause module.
		auto tmp = it++;
		(tmp->first)->unPause();
		pausedModules.erase(tmp);
	}
}


// Protected methods below.
////////////////////////////////


/*
 * Tracks paused module to re-enable it after specific time has passed.
 */
void Protothreading::trackPausedModule(Module * module, unsigned long us) {
	// Store paused module data for resuming module later.
	pausedModules[module] = std::make_pair(us, micros());
}

/*
 * Adds a callback to be called once paused module resumes.
 */
void Protothreading::addCallback(Module * module,
		std::function<void()> callback) {
	callbacks[module] = callback;
}
