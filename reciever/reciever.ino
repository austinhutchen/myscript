
#include "IRremote.h"
#include "Stepper.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "./BITS.c"
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
const byte rxPin = 2;
const byte txPin = 3;
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

  ushort getindex() { return this->index; }

  char refreshbuffer() {
    buf = mySerial.read();
    str[index] = buf;
    if (this->index == 15) {
      this->index = 0;
    }
    this->index++;
    return buf;
  }
  void prntstr() {
    // prints a column of our array
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
    lcd.setCursor(0, 1);
    lcd.print(millis() / 1000);
  }
};
void thumbsup() {
  byte thumb1[8] = {B00100, B00011, B00100, B00011,
                    B00100, B00011, B00010, B00001};
  byte thumb2[8] = {B00000, B00000, B00000, B00000,
                    B00000, B00000, B00000, B00011};
  byte thumb3[8] = {B00000, B00000, B00000, B00000,
                    B00000, B00000, B00001, B11110};
  byte thumb4[8] = {B00000, B01100, B10010, B10010,
                    B10001, B01000, B11110, B00000};
  byte thumb5[8] = {B00010, B00010, B00010, B00010,
                    B00010, B01110, B10000, B00000};
  byte thumb6[8] = {B00000, B00000, B00000, B00000,
                    B00000, B10000, B01000, B00110};
  lcd.createChar(0, thumb1);
  lcd.createChar(1, thumb2);
  lcd.createChar(2, thumb3);
  lcd.createChar(3, thumb4);
  lcd.createChar(4, thumb5);
  lcd.createChar(5, thumb6);
  lcd.setCursor(4, 1);
  lcd.write(byte(0));
  lcd.setCursor(4, 0);
  lcd.write(byte(1));
  lcd.setCursor(5, 1);
  lcd.write(byte(2));
  lcd.setCursor(5, 0);
  lcd.write(byte(3));
  lcd.setCursor(6, 1);
  lcd.write(byte(4));
  lcd.setCursor(6, 0);
  lcd.write(byte(5));
}

void thumbdownA() {
  byte thumb1[8] = {B00001, B00010, B00011, B00100,
                    B00011, B00100, B00011, B00100};
  byte thumb2[8] = {B00011, B00000, B00000, B00000,
                    B00000, B00000, B00000, B00000};
  byte thumb3[8] = {B11110, B00001, B00000, B00000,
                    B00000, B00000, B00000, B00000};
  byte thumb4[8] = {B00000, B11110, B01000, B10001,
                    B10010, B10010, B01100, B00000};
  byte thumb5[8] = {B00000, B10000, B01110, B00010,
                    B00010, B00010, B00010, B00010};
  byte thumb6[8] = {B00110, B01000, B10000, B00000,
                    B00000, B00000, B00000, B00000};
  lcd.createChar(0, thumb1);
  lcd.createChar(1, thumb2);
  lcd.createChar(2, thumb3);
  lcd.createChar(3, thumb4);
  lcd.createChar(4, thumb5);
  lcd.createChar(5, thumb6);
  lcd.setCursor(4, 0);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);
  lcd.write(byte(1));
  lcd.setCursor(5, 0);
  lcd.write(byte(2));
  lcd.setCursor(5, 1);
  lcd.write(byte(3));
  lcd.setCursor(6, 0);
  lcd.write(byte(4));
  lcd.setCursor(6, 1);
  lcd.write(byte(5));
}

void thumbdownB() {
  byte thumb1[8] = {B00000, B00001, B00010, B00011,
                    B00100, B00011, B00100, B00011};
  byte thumb2[8] = {B00100, B00011, B00000, B00000,
                    B00000, B00000, B00000, B00000};
  byte thumb3[8] = {B00000, B11110, B00001, B00000,
                    B00000, B00000, B00000, B00000};
  byte thumb4[8] = {B00000, B00000, B11110, B01000,
                    B10001, B10010, B10010, B01100};
  byte thumb5[8] = {B00000, B00000, B10000, B01110,
                    B00010, B00010, B00010, B00010};
  byte thumb6[8] = {B00010, B00110, B01000, B10000,
                    B00000, B00000, B00000, B00000};
  lcd.createChar(0, thumb1);
  lcd.createChar(1, thumb2);
  lcd.createChar(2, thumb3);
  lcd.createChar(3, thumb4);
  lcd.createChar(4, thumb5);
  lcd.createChar(5, thumb6);
  lcd.setCursor(4, 0);
  lcd.write(byte(0));
  lcd.setCursor(4, 1);
  lcd.write(byte(1));
  lcd.setCursor(5, 0);
  lcd.write(byte(2));
  lcd.setCursor(5, 1);
  lcd.write(byte(3));
  lcd.setCursor(6, 0);
  lcd.write(byte(4));
  lcd.setCursor(6, 1);
  lcd.write(byte(5));
}

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

void animate(unsigned x) {
  thumbdownA();
  delay(x);
  lcd.clear();
  thumbdownB();
  delay(x);
  lcd.clear();
  thumbsup();
  delay(x);
  lcd.clear();
}

short handleir(decode_results results) {
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    switch (results.value) {
      lcd.clear();
      lcd.setCursor(0, 0);
    case 0xFF629D:
      animate(700); // VOL+ button pressed
      delay(700);
      return 1;
    case 0xFFA857: // VOL- button pressed
      lcd.print("<SIGKILL..>");
      delete usr;
      usr = 0x0;
      delay(500);
      lcd.clear();
      return -1;
    default: {
      return 0;
    }
    }
  }
}

void loop() {
<<<<<<< HEAD
  while (mySerial.isListening() && handleir(results) != -1) {
    // print the number of seconds since reset:
    irrecv.resume(); // receive the next value
    unsigned char t = usr->refreshbuffer();
=======
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    switch (results.value)
    {
    case 0xFFA857:                 // VOL+ button pressed
      small_stepper.setSpeed(500); // Max seems to be 500
      Steps2Take = 2048;           // Rotate CW
      small_stepper.step(Steps2Take);
      delay(2000);
      break;
    case 0xFF629D: // VOL- button pressed
      small_stepper.setSpeed(500);
      Steps2Take = -2048; // Rotate CCW
      small_stepper.step(Steps2Take);
      delay(2000);
      break;
    }

    irrecv.resume(); // receive the next value
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
  if (mySerial.isListening()) {
    // print the number of seconds since reset:
    usr->refresh();
>>>>>>> efa62b6 (d)
    lcd.setCursor(0, 0);
    if (t != UCHAR_MAX) {
      lcd.clear();
      usr->prntstr();
      delay(300);
    } else {
      lcd.clear();
      lcd.print("<0xf>");
      lcd.setCursor(0, 1);
      lcd.print("-Enter input-");
      delay(300);
    }
    lcd.clear();
<<<<<<< HEAD
=======

  } else {
    delete usr;
    usr = 0x0;
    return;
>>>>>>> efa62b6 (d)
  }
  exit(0);
}