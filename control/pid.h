#ifndef PID_H

struct PIDparam{
    float KP = 0;
    float KI = 0;
    float KD = 0;
};

class PID{ //PID制御クラス
public:
  float execution(const float value, const float target);
  float exclusive(const float val, const float min, const float max);
  void setPID(const float KP, const float KI, const float KD);
  void setPID(const PIDparam pidparam);
  PIDparam getPID();
private:
  PIDparam pidparam;
  float error[2] = {};
  float integral = 0;
};

#define PID_H
#endif