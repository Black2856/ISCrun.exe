#include "section.h"

uint16_t Section::running(uint16_t currentSection){
  this->currentSection = currentSection;
  if(sectionEntry == false){
    sectionEntry = true;
    clock.reset();
    entry();
  }
  main();
  condition();
  return this->currentSection;
}

void Section::transition(const uint16_t sectionID){
  clock.reset();
  sectionEntry = false;
  this->currentSection = sectionID;
}