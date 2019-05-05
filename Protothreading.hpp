#ifndef PROTOTHREADING_H
#define PROTOTHREADING_H

#include <functional>
#include <map>
#include "Module.hpp"

class Protothreading {

	public:
		/* Pause module for some time in miliseconds. */
		static bool pause(Module * module, unsigned long ms);
		/* Pause module for some time in microseconds. */
		static bool pauseMicros(Module * module, unsigned long us);
		/* Pause module for some time in miliseconds,
		 * then invoke callback when resumes. */
		static bool pause(Module * module, unsigned long ms,
				void(*callback)(Module * module));
		/* Pause module for some time in microseconds,
		 * then invoke callback when resumes. */
		static bool pauseMicros(Module * module, unsigned long us,
				void(*callback)(Module * module));

		/* Checks to see whether paused modules should be resumed. */
		static void checkOnPausedModules();


	protected:
		/* Tracks paused module to re-enable it after duration passed. */
		static void trackPausedModule(Module * module, unsigned long us);

		/* Add callback to be called when module resumes. */
		static void addCallback(Module * module,
				void(*callback)(Module * module));

		/* Paused modules data. (map)
		 * Key: Module*
		 * Value: Pair <pauseDuration, pausedSince>
		 */
		static std::map<Module *,
			std::pair<unsigned long, unsigned long>> pausedModules;

		/* Module callbacks data. (map)
		 * Key: Module*
		 * Value: Callback to invoke.
		 */
		static std::map<Module *, void(*)(Module *)> callbacks;
    

};

#endif /* PROTOTHREADING_H */
