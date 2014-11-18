
#ifndef __ICONDVAR_H__
#define __ICONDVAR_H__

class ICondVar
{
public:
  virtual ~ICondVar() {}
  virtual void sleepCondVar() = 0;
  virtual void wakeCondVar() = 0;
};

#else

class ICondVar;

#endif
