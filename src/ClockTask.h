#ifndef CLOCKTASK_H
#define CLOCKTASK_H

#include <M5StickCPlus.h>
#include "frtesp32.h"
#include "DisplayTime.h"
#include "constants.h"

class ClockTask final : public frtesp32::Task<ClockTask, 10000> {
  public:
    bool run();
    int lang = SPANISH;
  private:
    int prevH, prevM = 0;
    int prevL = lang;
    RTC_TimeTypeDef TimeStruct;
};

#endif