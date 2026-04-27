# DLD-Project-report arduino code 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MUX_SELECT  4
#define LDR_PIN     A0
#define TEMP_PIN    A1

void setup() {
  pinMode(MUX_SELECT, OUTPUT);
  digitalWrite(MUX_SELECT, LOW);

  lcd.init();
  lcd.backlight();

  // 3-second intro screen
  lcd.setCursor(0, 0);
  lcd.print("Temp & Light");
  lcd.setCursor(0, 1);
  lcd.print("Data Logger");
  delay(3000);
  lcd.clear();
}

void loop() {
  // Read temperature from LM35
  int raw = analogRead(TEMP_PIN);
  float temp = (raw * 0.48828125) - 16.4;

  // Read light level from LDR
  int ldrValue = analogRead(LDR_PIN);
  String light;
  if (ldrValue < 200) {
    light = "Dark";
  } else if (ldrValue < 600) {
    light = "Dim";
  } else {
    light = "Bright";
  }

  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" C      ");

  lcd.setCursor(0, 1);
  lcd.print("Light: ");
  lcd.print(light);
  lcd.print("         ");

  delay(500);
}
