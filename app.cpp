#include "app.h"
#include "Clock.h"
#include "section_core.h"

using namespace ev3api;

static bool iscrunexeTerminate = false;
Clock clock;
SectionCore *sectionCore = new SectionCore(0);

void order_task(intptr_t exinf) {
  if(iscrunexeTerminate == false){
    iscrunexeTerminate = sectionCore->run();
  }
  ext_tsk();
}

void bluetooth_task(intptr_t exinf){
  ext_tsk();
}

void main_task(intptr_t unused) {

  sta_cyc(ORDER_CYC);
  sta_cyc(BLUETOOTH_CYC);
  
  while (iscrunexeTerminate == false) {
      clock.sleep(100*1000);
  }
  stp_cyc(ORDER_CYC);
  stp_cyc(BLUETOOTH_CYC);

  ext_tsk();
}
