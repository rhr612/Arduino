
#define BLYNK_TEMPLATE_ID "TMPL6rSk6NRF_"
#define BLYNK_TEMPLATE_NAME "HOME"
#define BLYNK_AUTH_TOKEN "lGKwIAYN4naSxZqgErffzCiLp9jpvCeh"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[]= BLYNK_AUTH_TOKEN;
char ssid[] = "Hello world";
char pass[] = "printf()";


int relay1=D1;
int relay2=D2;
int relay3=D3;
int relay4=D4;

int state1=1,state2=1,state3=1;


void setup()
{
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);
  digitalWrite(relay4,HIGH);
}

void loop()
{
  Blynk.run();

}

BLYNK_WRITE(V0)
{
  int val =param.asInt();
  Serial.println(val);
  if (val == 1){
    digitalWrite(relay1,!state1);
    Serial.print("Relay 1 is on");
  }
  if (val == 0){
    digitalWrite(relay1,state1);
    Serial.print("Relay 1 is off");
  }
}



BLYNK_WRITE(V1)
{
  int val =param.asInt();
  Serial.println(val);
  if (val == 1){
    digitalWrite(relay2,!state2);
    Serial.print("Relay 2 is on");
  }
  if (val == 0){
    digitalWrite(relay2,state2);
    Serial.print("Relay 2 is off");
  }
}


BLYNK_WRITE(V2)
{
  int val =param.asInt();
  Serial.println(val);
  if (val == 1){
    digitalWrite(relay3,!state3);
    Serial.print("Relay 3 is on");
  }
  if (val == 0){
    digitalWrite(relay3,state3);
    Serial.print("Relay 3 is off");
  }
}


//BLYNK_WRITE(V3)
//{
//  int val =param.asInt();
//  Serial.println(val);
//  if (val == 1){
//    digitalWrite(relay4,!state3);
//    Serial.print("Relay 4 is on");
//  }
//  if (val == 0){
//    digitalWrite(relay4,state3);
//    Serial.print("Relay 4 is off");
//  }
//}
