#include "section_core.h"
#include "stdio.h"

using namespace ev3api;

SectionCore::SectionCore(const SectionList sectionID){
  this->currentSection = sectionID;
}

bool SectionCore::run(){
  if(ev3_button_is_pressed(BACK_BUTTON)){//走行強制終了
    currentSection = SectionList::Section99;
    terminate = true;
  }

  currentSection = p_section[(int)currentSection]->running(currentSection);
  dataIO->dataOutput("data.csv");

  return terminate;
}