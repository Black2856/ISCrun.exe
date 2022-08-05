#include "run_area.h"
#include "sectionList.h"
#include "control.h"
#include "ev3f.h"
#include "measurement_core.h"
#include "calibration.h"

#include "stdio.h"
#include "cstdlib"

using namespace std;

EV3 *ev3 = EV3::getInstance();
Control *control = Control::getInstance();
MeasurementCore *measurementCore = MeasurementCore::getInstance();
BrightnessData brightnessData;

////////////////////////////////////////////////////////////////終了
void Section99::entry(){
    control->run.setParam(0,0,0,0);
    control->run.update();
    ev3->leftWheel.stop();
    ev3->rightWheel.stop();
    dataIO->addData("end", "end");
}

void Section99::main(){
}

void Section99::condition(){
}

////////////////////////////////////////////////////////////////開始待ち
void Section00::entry(){
    tslp_tsk(1000 * 1000); //初期化待ち
    control->run.setParam(5,-100,0,0);
}

void Section00::main(){
    control->run.update();
}

void Section00::condition(){
    if((int)ev3->rightWheel.getCount() > 1){
        control->run.setParam(0,0,0,0);
        control->run.update();
/*
        brightnessData.max = 35;
        brightnessData.min = 4;
        brightnessData.avg = 19;
        brightnessData.gain = 1.064516;
*/
        transition(SectionList::Section01);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション
void Section01::entry(){
    control->run.setParam(6,-100,0,0);
    measurementCore->vector.setRotateOffset();
}

void Section01::main(){
    control->run.update();
    measurementCore->calibration.addBrightness();
}

void Section01::condition(){
    if(ev3->GyroSensor_getAngle() >= 450){
        brightnessData = measurementCore->calibration.getBrightnessData(10);
        //printf("%d,%d,%d\n",brightnessData.max,brightnessData.min,brightnessData.avg);
        dataIO->addData("max", (int)brightnessData.max);
        dataIO->addData("min", (int)brightnessData.min);
        dataIO->addData("avg", (int)brightnessData.avg);
        dataIO->addData("gain", (float)brightnessData.gain);

        control->run.setParam(0,0,0,0);
        control->run.update();
        transition(SectionList::Section02);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション
void Section02::entry(){
    control->pid.setPID(1, 0.1, 0.2);
}

void Section02::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(fix,100,0,0);
    control->run.update();
}

void Section02::condition(){
    if((int)ev3->colorSensor.getBrightness() == brightnessData.avg){
        control->run.setParam(0,0,0,0);
        control->run.update();
        transition(SectionList::Section03);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション
void Section03::entry(){
}

void Section03::main(){
}

void Section03::condition(){
    if(ev3->touchSensor.isPressed()){
        transition(SectionList::Section04);
    }
}
////////////////////////////////////////////////////////////////走行エリア
void Section04::entry(){
    measurementCore->curve.resetCurve();
    control->pid.setPID(1.5,0,0.15); //シミュレータ2.4 0 0.4
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
}

void Section04::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    //control->run.setParam(100 - measurementCore->vector.getStable(100) * 1.8, (int)fix, 0, 0);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
    dataIO->addData("fix", (int)fix);
    dataIO->addData("stable10", measurementCore->vector.getStable(10));
    measurementCore->curve.updateCurve(brightnessData, fix);
    dataIO->addData("curve", measurementCore->curve.getCurve());
    //dataIO->addData("rotate", measurementCore->vector.getRotate(10));
    dataIO->addData("Angle", measurementCore->vector.getAngle());
    measurementCore->sensorOutput();
    dataIO->addData("Scalar", measurementCore->vector.getScalar());
}

void Section04::condition(){
    if(measurementCore->vector.getScalar() > 85){
        transition(SectionList::Section05);
    }
}
////////////////////////////////////////////////////////////////走行エリア

void Section05::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.2,0,0.1);
}

void Section05::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(30, (int)fix, 500 * 1000, 1);
    control->run.update();
    measurementCore->sensorOutput();
    dataIO->addData("Scalar", measurementCore->vector.getScalar());
    measurementCore->vector.addAnglerVelocity();
    measurementCore->curve.updateCurve(brightnessData, fix);
}

void Section05::condition(){
    if(abs(measurementCore->curve.getCurve() < 2500) && measurementCore->vector.getScalar() > 65){
        transition(SectionList::Section06);
    }
}

////////////////////////////////////////////////////////////////走行エリア
void Section06::entry(){
    measurementCore->curve.resetCurve();
    control->pid.setPID(1.5,0,0.15);
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
}

void Section06::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
}

void Section06::condition(){
    if(measurementCore->vector.getScalar() > 115){
        transition(SectionList::Section07);
    }
}

////////////////////////////////////////////////////////////////走行エリア

void Section07::entry(){
    measurementCore->curve.resetCurve();
    measurementCore->vector.setRotateOffset();
    control->pid.setPID(1.0,0,0.1);
}

void Section07::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(30, (int)fix, 500 * 1000, 1);
    control->run.update();
}

void Section07::condition(){
    if(abs(measurementCore->curve.getCurve() < 2500) && measurementCore->vector.getScalar() > 65){
        transition(SectionList::Section08);
    }
}

////////////////////////////////////////////////////////////////走行エリア

void Section08::entry(){
    measurementCore->curve.resetCurve();
    control->pid.setPID(1.5,0,0.15);
    measurementCore->vector.setRotateOffset();
    measurementCore->vector.resetAnglerVelocity();
}

void Section08::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(100, (int)fix, 0, 0);
    control->run.update();

    measurementCore->vector.addAnglerVelocity();
}

void Section08::condition(){
    if(measurementCore->vector.getScalar() > 100){
        transition(SectionList::Section99);
    }
}

/*
void Section99::entry(){
    //printf("entry99 ");
}

void Section99::main(){
    //printf("main99 ");
}

void Section99::condition(){
    //printf("condition99 ");
    //printf("%u\n",clock.now());
    if(clock.now() > 10000000){
        transition((int)SectionList::Section01);
    }
}
*/