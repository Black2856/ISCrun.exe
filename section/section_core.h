#ifndef SECTIONCORE_H
#include "stdint.h"
#include "run_area.h"
#include "section.h"
#include "curve.h"
#include "dataIO.h"
#include "ev3f.h"
#include "sectionList.h"

#include "ev3api.h"
#include "Clock.h"

class SectionCore{
public:
  SectionCore(const SectionList sectionID);
  bool run();

private:
  DataIO *dataIO = DataIO::getInstance();
  EV3 *ev3 = EV3::getInstance();
  Clock clock;

  uint64_t pressed = 0;
  SectionList currentSection;
  bool terminate = false; //走行終了管理

  Section99 section99;
  Section00 section00;
  Section01 section01;
  Section02 section02;
  Section03 section03;
  Section04 section04;
  Section05 section05;
  Section06 section06;
  Section07 section07;
  Section08 section08;
  Section *p_section[10] = {
    &section99,
    &section00,
    &section01,
    &section02,
    &section03,
    &section04,
    &section05,
    &section06,
    &section07,
    &section08
  };
};

#define SECTIONCORE_H
#endif