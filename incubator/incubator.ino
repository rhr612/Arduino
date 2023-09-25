#include <Servo.h>
#include <DHT.h>
#include <DHT_U.h>
#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define DHTPIN 5   

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Servo myservo;

extern volatile unsigned long timer0_millis;
unsigned long t1,x=0;
int Time=90;
float uptemp=37;
float lowtemp=35;
float lowhum=65;
int turn=1;
int pos = 0;
int light=13,hmod=12;
int ht=0;


void setup() {
  Serial.begin(9600);
  turn=EEPROM.read("val");
  if(turn==1){myservo.write(170);}
  else{myservo.write(0);}
  pinMode(light,OUTPUT);
  pinMode(hmod,OUTPUT);
  digitalWrite(hmod,HIGH);
  myservo.attach(6);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  
}

void loop() {
  
  t1=millis();
  Serial.print("mil  :  ");
  Serial.print(t1/1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  



  
  
  if(t1/1000==60){ //////////////////////reset milis
    x=x+1;
    noInterrupts ();
    timer0_millis = 0;
    interrupts ();
  }
  
  Serial.print("       ");
  Serial.print("sec  :  ");
  Serial.print(x);
  Serial.print("       ");
  Serial.print("t  :  ");
  Serial.print(turn);
  Serial.print("       ");
  

  Serial.print("Hum: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temp: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.println("");
  lcd.setCursor(0, 0);
  lcd.print("TEMP :");
  lcd.print(t);
  lcd.print(" TU:");
  lcd.print(turn);
  lcd.setCursor(0, 1);
  lcd.print("HUM :");
  lcd.print(h);
  lcd.print(" M:");
  lcd.print(x);
  
  if(x==Time && turn==255){

      for (pos = 0; pos <= 170; pos += 1) { 
      myservo.write(pos);
      delay(15);
    }
    turn=1;
    EEPROM.write("val",turn);
    noInterrupts ();
    timer0_millis = 0;
    interrupts ();
    x=0;
    ht=0;
    
   }



  if(x==Time && turn==1){

      for (pos = 170; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15); 
      }
      turn=255;
      EEPROM.write("val",turn);
      noInterrupts ();
      timer0_millis = 0;
      interrupts ();
      x=0;
      ht=0;
 }
  
  if(t>=uptemp){
    digitalWrite(light,HIGH);
  }

 if(t<=lowtemp){
    digitalWrite(light,LOW);
  }
  
 if(x-ht==1){
  if(h<lowhum){
    digitalWrite(hmod,LOW);
    ht=x;
    delay(5000);
    digitalWrite(hmod,HIGH);
  }
 }
  }
