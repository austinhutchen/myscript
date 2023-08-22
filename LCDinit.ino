#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define INT_MAX pow(2, 32) - 1
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
SoftwareSerial mySerial(2, 3);
struct user {
  unsigned long buf;
  user() { buf = 0; }
  unsigned long func() { return buf; }
  refresh() { buf = mySerial.read(); }
};
user *usr = new user();

void setup() {
  mySerial.begin(9600); // Setting the baud rate of Software Serial Library
  Serial.begin(9600);   // Setting the baud rate of Serial Monitor
  Serial.println("starting up...");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  // print the number of seconds since reset:
  usr->refresh();
  lcd.setCursor(0, 0);
  auto t = usr->func();
  if (t != INT_MAX) {
    lcd.print(t);
  } else {
    lcd.print("ERR");
  }
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  delay(100);
  lcd.clear();
}