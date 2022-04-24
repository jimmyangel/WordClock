#include <M5StickCPlus.h>
#include <ArduinoLog.h>

const int SPANISH = 0;
const int ENGLISH = 1;

class TimeWords  {
  public:
    String &getWords(int hour, int minutes, int lang);
  private: 
    static String preText[2][2];
    static String postText[2][1];
    static String articleText[2][2];
    static String fractionText[2][4];
    static String numbersText[2][12];
    static String numbersModText[2][11];
    String fT;
};