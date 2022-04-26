#include "TimeSync.h"

void timeSync(String &ssid, String &password) {
  RTC_TimeTypeDef TimeStruct;
  RTC_DateTypeDef DateStruct;
  const char* ntpServer =  "pool.ntp.org";
  const long gmtOffset_sec = -8*3600;
  const int daylightOffset_sec = 3600;
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