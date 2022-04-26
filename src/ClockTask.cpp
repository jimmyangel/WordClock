#include "ClockTask.h"

bool ClockTask::run() {
  M5.Rtc.GetTime(&TimeStruct);
  if (prevM != TimeStruct.Minutes || prevH != TimeStruct.Hours || prevL != lang) {
    prevH = TimeStruct.Hours; prevM = TimeStruct.Minutes; prevL = lang;
    displayTime(TimeStruct.Hours, TimeStruct.Minutes, lang);
  }
  msleep(1000);
  return true;
}