#include "section_core.h"
#include "stdio.h"

using namespace ev3api;

SectionCore::SectionCore(const uint16_t sectionID){
  this->currentSection = sectionID;
}

bool SectionCore::run(){
  if(ev3->touchSensor.isPressed()){
    if(pressed == 0){
      clock.reset();
      pressed = 1;
    }else if(pressed == 1 && clock.now() > (1000 * 1000)){
      currentSection = 99;
    }
  }else{
    pressed = 0;
  }

  currentSection = p_section[currentSection]->running(currentSection);
  dataIO->dataOutput("data.csv");

  if(currentSection == 99){
    terminate = true;
  }

  return terminate;
}