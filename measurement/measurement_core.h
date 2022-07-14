#ifndef MEASUREMENTCORE_H
#include "dataIO.h"
#include "ev3f.h"
#include "calibration.h"
#include "vector.h"

class MeasurementCore{ //計測系のSingleton管理クラス
public:
    static MeasurementCore* getInstance();
    void sensorOutput();
    Calibration calibration;
    Vector vector;
    
private:
    MeasurementCore();
    ~MeasurementCore();
    static MeasurementCore* m_Measurement;

    EV3 *ev3 = EV3::getInstance();
    DataIO *dataIO = DataIO::getInstance();
};

#define MEASUREMENTCORE_H
#endif