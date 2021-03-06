#ifndef TIMEWORDS_H
#define TIMEWORDS_H
#include <M5StickCPlus.h>
#include "constants.h"

class TimeWords  {
  public:
    String &getWords(int hour, int minutes, int lang);
  private: 
    static String preText[2][2];
    static String postText[2][1];
    static String articleText[2][2];
    static String fractionText[2][4];
    static String numbersText[2][12];
    static String numbersModText[2][12];
    String fT;
};

#endif