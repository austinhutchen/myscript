
#include "./BITS.c"
#include "IRremote.h"
#include "Stepper.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
/*----- Variables, Pins -----*/
#define STEPS 32  // Number of steps per revolution of Internal shaft
int Steps2Take;   // 2048 = 1 Revolution
int receiver = 5; // Signal Pin of IR receiver to Arduino Digital Pin 6

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 2, 3, 4, 6);
IRrecv irrecv(receiver); // create instance of 'irrecv'
decode_results results;  // create instance of 'decode_results'
#define UCHAR_MAX pow(2, 8) - 1
// initialize the library with the numbers of the interface pins11
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
const byte rxPin = 0;
const byte txPin = 1;
SoftwareSerial mySerial(rxPin, txPin);
char array[8];

