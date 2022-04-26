#include "DisplayTime.h"

TimeWords tW;

void displayTime(int hours, int minutes, int lang) {
  if (lang != SPANISH) lang = ENGLISH;
  String t = tW.getWords(hours, minutes, lang);
  int start = 0;
  int end = 16;
  int i = 0;
  M5.Lcd.fillScreen(BLACK);
  do {
    end = t.lastIndexOf(' ', end);
    String line = t.substring(start, end);
    line.trim();
    M5.Lcd.setCursor(0, (24 * i++) + 10, 4);
    M5.Lcd.print(line);
    start = end;
    end = start + 16;
    if (end > t.length()) end = t.length();
  } while (start < t.length());

}