#include <M5StickCPlus.h>
#include <Preferences.h>
#include <WiFi.h>
#include <time.h>
#include "DisplayTime.h"

Preferences preferences;

String ssid;
String password;

const char* ntpServer =  "pool.ntp.org";
const long gmtOffset_sec = -8*3600;
const int daylightOffset_sec = 3600;

RTC_TimeTypeDef TimeStruct;
RTC_DateTypeDef DateStruct;

void timeSync() {
  struct tm timeInfo;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to WiFi ..");
  for (int i=0; i<15 && WiFi.status() != WL_CONNECTED; i++) {
    Serial.print('.');
    M5.Lcd.print('.');
    delay(1000);
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi Connected ");
    Serial.println(WiFi.localIP());
    delay(50);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    if (getLocalTime(&timeInfo)){
      Serial.println("Time retrieved");
      TimeStruct.Hours = timeInfo.tm_hour;
      TimeStruct.Minutes = timeInfo.tm_min;
      TimeStruct.Seconds = timeInfo.tm_sec;
      DateStruct.WeekDay = timeInfo.tm_wday;
      DateStruct.Month = timeInfo.tm_mon;
      DateStruct.Date = timeInfo.tm_mday;
      DateStruct.Year = timeInfo.tm_year;
      M5.Rtc.SetTime(&TimeStruct);
    } else {
      Serial.println("Could not sync time");
    }
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    Serial.println("WiFi Disconnected");
  } else {
    Serial.println("Could not connect to WIFi");
  }
}

void setup() {
  M5.begin(true, true, true);
  Serial.begin(115200);

  preferences.begin("wordclockwifi", false);
 
  ssid = preferences.getString("ssid", ""); 
  password = preferences.getString("password", "");

  timeSync();

  M5.Lcd.setRotation(3);
  M5.Axp.ScreenBreath(9);

  xTaskCreate(clockTask, "Clock Task", 10000, NULL, 1, NULL);

}

int lang = SPANISH;

void clockTask(void * parm) {
  int prevH, prevM = 0;
  int prevL = lang;
  while (true) {
    M5.Rtc.GetTime(&TimeStruct);
    if (prevM != TimeStruct.Minutes || prevH != TimeStruct.Hours || prevL != lang) {
      prevH = TimeStruct.Hours; prevM = TimeStruct.Minutes; prevL = lang;
      displayTime(TimeStruct.Hours, TimeStruct.Minutes, lang);
    }
    delay(1000);
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
