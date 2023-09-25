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
  pinMode(light,OUTPUT);
  pinMode(hmod,OUTPUT);
  digitalWrite(hmod,HIGH);
  myservo.attach(6);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  
}

void loop() {
  

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  lcd.setCursor(0, 0);
  lcd.print("TEMP :");
  lcd.print(t);

  lcd.setCursor(0, 1);
  lcd.print("HUM :");
  lcd.print(h);
  
 
  
  if(t>=uptemp){
    digitalWrite(light,HIGH);
  }

 if(t<=lowtemp){
    digitalWrite(light,LOW);
  }
  

  if(h<lowhum){
    digitalWrite(hmod,LOW);
  }
    if(h>lowhum){
    digitalWrite(hmod,HIGH);
  }
  }
