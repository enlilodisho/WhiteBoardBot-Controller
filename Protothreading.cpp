/** Project       : White Board Bot Controller
    ----------------------------------------------------------
    File          : Protothreading.cpp
    Description   : "Static" class containing useful methods for protothreading.
*/

#include "Arduino.h"
#include "Protothreading.h"

/*
 * Store a hash table of timers.
 * Key: Timer unique id.
 * Value: Pair( interval, time_startedS(us) )
 */
std::map<unsigned int, std::pair<unsigned long, long long>> Protothreading::timersMap;

/*
 * The next available timer id.
 */
unsigned int Protothreading::nextAvailableTimerId = 0;

/*
 * Start a timer with miliseconds interval.
 * Returns Timer id.
 */
unsigned int Protothreading::timer(unsigned long ms) {
  unsigned int timerId = nextAvailableTimerId++;
  timer(timerId, ms);
  return timerId;
}

/*
 * Start a timer with microseconds interval.
 * Returns Timer id.
 */
unsigned int Protothreading::timerMicroseconds(unsigned long us) {
  unsigned int timerId = nextAvailableTimerId++;
  timerMicroseconds(timerId, us);
  return timerId;
}

/*
 * Resets the timer.
 */
bool Protothreading::timerReset(unsigned int id) {
  auto it = timersMap.find(id);
  if (it == timersMap.end()) {
    return false;
  }
  ((*it).second).second = micros();
  return true;
}

/*
 * Deletes timer.
 */
void Protothreading::timerDelete(unsigned int id) {
  auto it = timersMap.find(id);
  if (it == timersMap.end()) {
    return;
  }
  timersMap.erase(it);
}

/*
 * Returns boolean on whether timer finished.
 * Deletes timer after.
 */
bool Protothreading::timerCheckAndDelete(unsigned int id) {
  auto it = timersMap.find(id);
  bool result;
  if (result = timerCheck(it)) {
    timersMap.erase(it);
  }
  return result;
}

/*
 * Returns boolean on whether timer finished.
 * Keeps timer in memory after (for usage later).
 * Warning: Make sure to remove timer when done with it!
 */
bool Protothreading::timerCheckAndSave(unsigned int id) {
  auto it = timersMap.find(id);
  return timerCheck(it);
}

/*
 * Change timer interval. (miliseconds)
 */
void Protothreading::timerChangeIntervalMS(unsigned int id, unsigned long ms) {
  timerChangeIntervalUS(id, ms*1000);
}

/*
 * Change timer interval. (microseconds)
 */
void Protothreading::timerChangeIntervalUS(unsigned int id, unsigned long us) {
  auto it = timersMap.find(id);
  if (it == timersMap.end()) {
    return;
  }
  ((*it).second).first = us;
}

/////////////////////////////////////
// Private methods below

/*
 * Returns boolean on whether timer finished.
 */
bool Protothreading::timerCheck(std::map<unsigned int, std::pair<unsigned long, long long>>::iterator it) {
  if (it == timersMap.end()) {
    #ifdef DEBUG_MODE
      Serial.print("WARNING - Protothreading.cpp: Tried to check on invalid timer '");
      Serial.print(id);
      Serial.println("'");
    #endif
    return true;
  }
  if (((*it).second).second > 0 && micros() - ((*it).second).second > ((*it).second).first) {
    ((*it).second).second = -1; // stop timer.
    return true;
  } else {
    return false;
  }
}

/*
 * Creates and starts a timer with miliseconds interval.
 */
std::pair<unsigned long, unsigned long> Protothreading::timer(unsigned int id, unsigned long ms) {
  auto timer = timerMicroseconds(id, ms*1000);
  // Convert to miliseconds.
  timer.first /= 1000;
  timer.second /= 1000;
  return timer;
}

/*
 * Creates and starts a timer with microseconds interval.
 */
std::pair<unsigned long, unsigned long> Protothreading::timerMicroseconds(unsigned int id, unsigned long us) {
  std::map<unsigned int, std::pair<unsigned long, long long>>::const_iterator it = timersMap.find(id);
  if (it != timersMap.end()) {
    // Timer exists, return microseconds left.
    return (*it).second;
  }
  // Timer does not exist. Create and return.
  std::pair<unsigned long, long long> timer(us, micros());
  timersMap[id] = timer;
  return timersMap[id];
}
