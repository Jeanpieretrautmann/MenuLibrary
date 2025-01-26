#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <menu.hpp>

void action1() {
  Serial.println("Aktion 1 ausgeführt!");
}

void action2() {
  Serial.println("Aktion 2 ausgeführt!");
}

MenuItem items[] = {
  {"Option 1", action1},
  {"Option 2", action2}
};

Menu menu;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setBacklight(true);
  menu.begin(items, 2, 2, lcd);
}

void loop() {
  menu.display();

  if (digitalRead(2) == LOW) {
    menu.navigate(-1);
    delay(200);
  }
  if (digitalRead(3) == LOW) {
    menu.navigate(1);
    delay(200);
  }
  
  if (digitalRead(4) == LOW) {
    menu.select();
    delay(500);
  }

  delay(100);
}
