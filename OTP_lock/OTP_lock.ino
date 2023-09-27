
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial gsm(3, 2);
#include <Keypad.h>

// Password Length
const int Password_Length = 4;
// Character to hold password input
String Data;
// Password
String password;

int mode=1  ;   //home=1  psword_gen=2   enter pass =3 




// Pin connected to lock relay signal
int relay = A1;
int error=0;

// Counter for character entries
byte data_count = 0;

// Character to hold key input
char customKey;

// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;

// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Connections to Arduino
byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 5, 4};

// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Create LCD object : Use 0x27 If 0x3F Doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Setup LCD with backlight and initialize
  lcd.begin();
  Serial.begin(9600);
  gsm.begin(9600);
  lcd.backlight();
  randomSeed(analogRead(0));

  // Set relay as an OUTPUT pin
  pinMode(relay, OUTPUT);
}

void loop() {

  customKey = customKeypad.getKey();
  Serial.print(customKey);

  if (mode==1){
    mode1();
   }
   else if (mode==2){
    mode2();
   }
  else if (mode==3){
    mode3();
   }

   else if (mode==4){
    mode4();
   }

}

void clearData() {
  data_count = 0;
  Data ="";
}
