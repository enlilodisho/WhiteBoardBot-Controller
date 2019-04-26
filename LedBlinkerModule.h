#ifndef LEDBLINKER_MODULE_H
#define LEDBLINKER_MODULE_H

#include "Module.h"

class LedBlinkerModule: public Module {
  
public:
  ~LedBlinkerModule();
  
  bool initialize();
  void runTasks();

private:
  int timer1, timer2;
  
};

#endif /* LEDBLINKER_MODULE_H */
