#include <M5StickCPlus.h>
#include <ArduinoLog.h>
#include "DisplayTime.h"

void setup() {
  M5.begin(true, true, true);
  Serial.begin(115200);

  Log.begin(LOG_LEVEL_TRACE, &Serial);
  M5.Lcd.setRotation(3);
  M5.Axp.ScreenBreath(9);

  xTaskCreate(clockTask, "Clock Task", 10000, NULL, 1, NULL); 

}

int lang = SPANISH;

void clockTask(void * parm) {
  while (true) {
    displayTime(0, 1, lang);
    delay(5000);
    displayTime(0, 0, lang);
    delay(5000);
    displayTime(12, 49, lang);
    delay(5000);
    displayTime(14, 31, lang);
    delay(5000);
    displayTime(14, 32, lang);
    delay(5000);
    displayTime(16, 27, lang);
    delay(5000);
    displayTime(0, 10, lang);
    delay(5000);
  }
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) { 
    Serial.println("Button A was Pressed.");
    lang = !lang;
  }
  if (M5.BtnB.wasPressed()) { 
    Serial.println("Button B was Pressed.");
  }
}
