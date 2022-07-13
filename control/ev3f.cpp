#include "ev3f.h"

EV3* EV3::m_EV3 = NULL;

EV3::EV3():
    leftWheel(LEFTWHEEL), 
    rightWheel(RIGHTWHEEL),
    colorSensor(COLORSENSOR), 
    gyroSensor(GYROSENSOR),
    sonarSensor(SONARSENSOR),
    touchSensor(TOUCHSENSOR){}

EV3::~EV3(){
}

EV3* EV3::getInstance(){
    if (m_EV3 == NULL){
        m_EV3 = new EV3();
    }
    return m_EV3;
}