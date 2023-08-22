#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#define INT_MAX pow(2, 32) - 1
// initialize the library with the numbers of the interface pins11
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial mySerial(rxPin, txPin);
char array[8];
typedef char *iterator;
iterator array_begin(char a[]) { return &a[0]; }
iterator array_end(char a[], int n) { return &a[n]; }
iterator array_next(iterator i) { return ++i; }

struct user {
  char buf;
  char **str;
  int size;
  user() {
    buf = size = 0;
    str = 0x0;
  }
  char getbuf() {
    str += buf;
    this->size += 1;
    return buf;
  }
  void refresh() { buf = mySerial.read(); }
  void prnt() {
    int i = 0;
    iterator it = array_begin(*this->str);
    iterator end = array_end(*this->str, 15);
    for (; it != end ; it = array_next(it)) {
      lcd.print(*it);
      lcd.setCursor(i, 0);
      i++;
      delay(100);
    }
  }
};

user *usr = new user();

void setup() {
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600); // Setting the baud rate of Software Serial Library
  Serial.begin(9600);   // Setting the baud rate of Serial Monitor
  Serial.println("starting up...");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

void loop() {
  if (mySerial.isListening()) {
    // print the number of seconds since reset:
    usr->refresh();
    lcd.setCursor(0, 0);
    char t = usr->getbuf();
    if (t != WCHAR_MAX) {
      usr->prnt();
    } else {
      lcd.print("ERR");
    }
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    delay(100);
    lcd.clear();

  } else {
    delete usr;
    usr = 0x0;
    return;
  }

  // usr need to be deallocated
}