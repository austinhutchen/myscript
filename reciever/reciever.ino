
#include "./BITS.c"
#include "IRremote.h"
#include "Stepper.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
/*----- Variables, Pins -----*/
#define STEPS 32  // Number of steps per revolution of Internal shaft
int Steps2Take;   // 2048 = 1 Revolution
int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 6
#define ushort unsigned short
#define UCHAR_MAX pow(2, 8) - 1
/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const byte rxPin = 0;
const byte txPin = 1;
SoftwareSerial mySerial(rxPin, txPin);
char array[8];
typedef char *iterator;
iterator array_begin(char a[]) { return &a[0]; }
iterator array_end(char a[], int n) { return &a[n]; }
iterator array_next(iterator i) { return ++i; }
Stepper small_stepper(STEPS, 2, 3, 4, 6);
IRrecv irrecv(receiver); // create instance of 'irrecv'
decode_results results;  // create instance of 'decode_results'
// initialize the library with the numbers of the interface pins11

struct user {
  char buf;
  char str[16];
  ushort index;
  // line will be used to switch between the two display rows
  bool row;
  user() {
    buf = 0;
    index = 0;
    row = false;
  }
  char getbuf() {
    str[index] = buf;
    this->index++;
    return buf;
  }

  ushort getindex() { return this->index; }
  void wrapindex() {
    if (this->index == 15) {
      this->index = 0;
    }
    return;
  }
  void refreshbuffer() { buf = mySerial.read(); }
  void prntstr() {
    int i = 0;
    iterator it = array_begin(this->str);
    iterator end = array_end(this->str, 15);
    for (; it != end; it = array_next(it)) {
      lcd.setCursor(i, 0);
      lcd.print(*it);
      i++;
    }
    lcd.setCursor(8, 1);
    lcd.print(leftBitCount(this->str));
    delay(100);
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
    delay(200);
  }
};

user *usr = new user();

void setup() {
  irrecv.enableIRIn(); // Start the receiver
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  mySerial.begin(9600); // Setting the baud rate of Software Serial Library
  Serial.begin(9600);   // Setting the baud rate of Serial Monitor
  Serial.println("starting up...");
  lcd.print("starting up...");
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  delay(150);
  lcd.clear();
}

void loop() {
  while (mySerial.isListening()) {
    // print the number of seconds since reset:
    if (irrecv.decode(&results)) // have we received an IR signal?
    {
      switch (results.value) {
        lcd.clear();
        lcd.setCursor(0, 0);
      case 0xFFA857:
        lcd.print("Hello!"); // VOL+ button pressed
        delay(1000);
      case 0xFF629D: // VOL- button pressed
        lcd.print("EXITING...");
        delay(1000);
        delete usr;
        usr = 0x0;
        return;
      }
      irrecv.resume(); // receive the next value
    }
    usr->refreshbuffer();
    lcd.setCursor(0, 0);
    unsigned char t = usr->getbuf();
    if (t != UCHAR_MAX) {
      lcd.clear();
      usr->prntstr();
      delay(300);
    } else {
      lcd.clear();
      lcd.print("<0xff> Awaiting..");
      lcd.setCursor(0, 1);
      lcd.print("!enter input!");
      delay(300);
    }
    usr->wrapindex();
    lcd.clear();
  }
}
