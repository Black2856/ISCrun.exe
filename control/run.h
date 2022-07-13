#ifndef RUN_H
#include "ev3f.h"
#include "Clock.h"
#include "stdint.h"

struct RunParam{
    int PWM = 0; //速度(-100 ~ 100)
    int steering = 0; //ステアリング量(-100 ~ 100)
    uint64_t transitionTime = 0; //目標PWM値までの時間(usec)
    uint8_t steeringType = 0; //ステアリング計算方法の変更
};

class Run{
public:
    void update(); //EV3クラスの値更新
    void setParam(RunParam runParam);
    void setParam(int PWM, int steering, uint64_t transitionTime, uint8_t steeringType);
private:
    void steeringA(float &rightSteering, float &leftSteering, const int setPWM);
    void steeringB(float &rightSteering, float &leftSteering);
    EV3 *ev3 = EV3::getInstance();
    Clock clock;
    RunParam runParam;
    RunParam lastRunParam;
};

#define RUN_H
#endif