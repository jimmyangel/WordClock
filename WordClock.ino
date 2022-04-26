#include <M5StickCPlus.h>
#include <Preferences.h>
#include <WiFi.h>
#include <time.h>
#include "timesync.h"
#include "src/ClockTask.h"

portMUX_TYPE frtesp32::mux = portMUX_INITIALIZER_UNLOCKED;

Preferences preferences;

String ssid;
String password;

ClockTask clockTask;

void setup() {
  M5.begin(true, true, true);
  Serial.begin(115200);

  preferences.begin("wordclockwifi", false);

  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");

  M5.Lcd.setRotation(3);
  M5.Axp.ScreenBreath(9);

  timeSync(ssid, password);

  clockTask.start(1);

}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    Serial.println("Button A was Pressed.");
    clockTask.lang = !clockTask.lang;
  }
  if (M5.BtnB.wasPressed()) {
    Serial.println("Button B was Pressed.");
  }
}
