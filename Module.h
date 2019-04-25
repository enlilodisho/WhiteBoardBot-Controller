#ifndef MODULE_H
#define MODULE_H

class Module {

public:
  Module();
  virtual ~Module();

  virtual bool initialize() = 0;
  virtual void runTasks() = 0;
};

#endif
