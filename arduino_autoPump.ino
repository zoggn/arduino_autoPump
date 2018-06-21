#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define button1 3
#define rel_pin  9

int millisec = 1000;
unsigned long int waitTime = 30;
unsigned long int delayTime = 15;
unsigned long int currentTime = 0;
boolean pumpState = false;
int menuOrSettings = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);

  pinMode(button1, INPUT_PULLUP);
  attachInterrupt(1, OnButtonClick, FALLING);

  pinMode(rel_pin, OUTPUT);
  digitalWrite(rel_pin, HIGH);

  lcd.init();
}

void loop() {

  if (digitalRead(rel_pin) == 1) {
    if ((millis() - currentTime) >= waitTime * millisec) {
      digitalWrite(rel_pin, LOW);
      currentTime = millis();
      Serial.println("Pump Enabled");
      pumpState = true;
    }
  } else if (digitalRead(rel_pin) == 0) {
    if ((millis() - currentTime) >= delayTime * millisec) {
      digitalWrite(rel_pin, HIGH);
      currentTime = millis();
      Serial.println("Pump Disabled");
      pumpState = false;
    }
  }

  if (menuOrSettings == 0 ) {
    lcd.clear();
    lcd.noBacklight();
  } else if (menuOrSettings == 1) {
    if ((millis() - currentTime) >= 2000)
      main_menu();
  }
}

void OnButtonClick() {
  menuOrSettings++;
  if (menuOrSettings > 2) {
    menuOrSettings = 0;
  }
}

void main_menu() {
  lcd.backlight();
  lcd.setCursor(0, 0);
  if (pumpState == true) {
    if (((millis() - currentTime) / millisec) >= 10) {
      lcd.print("Pump enabled: "); lcd.setCursor(14, 0); lcd.print((millis() - currentTime) / millisec);
    } else {
      lcd.print("Pump enabled: "); lcd.setCursor(14, 0); lcd.print((millis() - currentTime) / millisec); lcd.setCursor(15, 0); lcd.print(" ");
    }
  } else {
    if ((waitTime - (millis() - currentTime) / millisec) >= 10) {
      lcd.print("Enable after: "); lcd.setCursor(14, 0); lcd.print((waitTime - (millis() - currentTime) / millisec));
    } else {
      lcd.print("Enable after: "); lcd.setCursor(14, 0); lcd.print((waitTime - (millis() - currentTime) / millisec)); lcd.setCursor(15, 0); lcd.print(" ");
    }
  }
}
