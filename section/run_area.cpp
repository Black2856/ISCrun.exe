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
}

void Section99::main(){
}

void Section99::condition(){
}

////////////////////////////////////////////////////////////////開始待ち
void Section00::entry(){
    control->run.setParam(5,-100,0,0);
}

void Section00::main(){
    control->run.update();
}

void Section00::condition(){
    if((int)ev3->rightWheel.getCount() > 1){
        control->run.setParam(0,0,0,0);
        control->run.update();
        transition((int)SectionList::Section01);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション
void Section01::entry(){
    control->run.setParam(6,-100,0,0);
}

void Section01::main(){
    control->run.update();
    measurementCore->calibration.addBrightness();
}

void Section01::condition(){
    if((int)ev3->rightWheel.getCount() > 1350/2){
        brightnessData = measurementCore->calibration.getBrightnessData(10);
        //printf("%d,%d,%d\n",brightnessData.max,brightnessData.min,brightnessData.avg);
        dataIO->addData("max", (int)brightnessData.max);
        dataIO->addData("min", (int)brightnessData.min);
        dataIO->addData("avg", (int)brightnessData.avg);
        dataIO->addData("gain", (float)brightnessData.gain);
        control->run.setParam(0,0,0,0);
        control->run.update();
        transition((int)SectionList::Section02);
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
        transition((int)SectionList::Section03);
    }
}
////////////////////////////////////////////////////////////////キャリブレーション
void Section03::entry(){
}

void Section03::main(){
}

void Section03::condition(){
    if(ev3->touchSensor.isPressed()){
        transition((int)SectionList::Section04);
    }
}
////////////////////////////////////////////////////////////////走行エリア
void Section04::entry(){
    control->pid.setPID(1.5,0,0.15); //シミュレータ2.4 0 0.4
}

void Section04::main(){
    float fix = control->pid.execution((float)measurementCore->calibration.getCorrectionVal(ev3->colorSensor.getBrightness(), brightnessData), SIM_AVG_BRIGHTNESS);
    control->run.setParam(100,(int)fix,0,0);
    control->run.update();

    dataIO->addData("fix", (int)fix);
    measurementCore->sensorOutput();
}

void Section04::condition(){
}
////////////////////////////////////////////////////////////////


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