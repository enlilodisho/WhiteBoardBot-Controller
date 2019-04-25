#ifndef PROTOTHREADING_H
#define PROTOTHREADING_H

#include "Module.h"
#include <map>

class Protothreading: public Module {

public:
  ~Protothreading();
  
  bool initialize();
  void runTasks();

  static unsigned int timer(unsigned long ms);
  static unsigned int timerMicroseconds(unsigned long us);
  static bool timerReset(unsigned int id);
  static bool timerCheckAndDelete(unsigned int id);
  static bool timerCheckAndSave(unsigned int id);
  static void timerChangeIntervalMS(unsigned int id, unsigned long ms);
  static void timerChangeIntervalUS(unsigned int id, unsigned long us);

private:
  static std::map<unsigned int, std::pair<unsigned long, long long>> timersMap;
  static unsigned int nextAvailableTimerId;

  static std::pair<unsigned long, unsigned long> timer(unsigned int id, unsigned long ms);
  static std::pair<unsigned long, unsigned long> timerMicroseconds(unsigned int id, unsigned long us);
  static bool timerCheck(std::map<unsigned int, std::pair<unsigned long, long long>>::iterator it);

};

#endif
