#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include "Module.h"

class MotorDriver: public Module {

public:
  MotorDriver(int penable, int preset, int psleep, int pstep, int pdir);
  ~MotorDriver();

  bool initialize();
  void runTasks();

  void motorStep();
  void sleep();
  void wake();
  void enable();
  void disable();
  void setDirectionFWD();
  void setDirectionREV();

private:
  const int pinEnable;
  const int pinReset;
  const int pinSleep;
  const int pinStep;
  const int pinDirection;

  int stepTimer;
  
};

#endif /* MOTOR_DRIVER_H */
