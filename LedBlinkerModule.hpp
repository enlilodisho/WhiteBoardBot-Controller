#ifndef LEDBLINKER_MODULE_H
#define LEDBLINKER_MODULE_H

#include "Module.hpp"

class LedBlinkerModule: public Module {

	public:
		~LedBlinkerModule();

		bool initialize();
		void runTasks();
    static void toggleLed(Module * module);

  private:
    bool ledPinHigh;

};

#endif /* LEDBLINKER_MODULE_H */
