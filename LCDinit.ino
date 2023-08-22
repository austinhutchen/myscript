#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
SoftwareSerial mySerial(2, 3);
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  // print the number of seconds since reset:
  lcd.setCursor(0, 0);
  lcd.print(mySerial.read());
  lcd.setCursor(0, 1);
  lcd.print(millis() / 100);
  delay(100);
  lcd.clear();
}