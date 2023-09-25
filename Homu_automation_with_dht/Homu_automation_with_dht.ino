
#define BLYNK_TEMPLATE_ID "TMPL6rSk6NRF_"
#define BLYNK_TEMPLATE_NAME "HOME"
#define BLYNK_AUTH_TOKEN "lGKwIAYN4naSxZqgErffzCiLp9jpvCeh"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>
#include <DHT.h>


char auth[]= BLYNK_AUTH_TOKEN;
char ssid[] = "Hello world";
char pass[] = "printf()";


#define DHT_PIN D4
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);


int relay1=D1;
int relay2=D2;
int relay3=D3;
int relay4=D4;
int val1,val2,val3;


void setup()
{
  EEPROM.begin(800);
  Serial.begin(115200);
  dht.begin();

  val1 = EEPROM.read(1);
  val2 = EEPROM.read(2);
  val3 = EEPROM.read(3);
  
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  digitalWrite(relay3,HIGH);


  digitalWrite(relay1, !val1);
  digitalWrite(relay2, !val2);
  digitalWrite(relay3, !val3);

  EEPROM.put(1, val1);
  EEPROM.put(2, val2);
  EEPROM.put(3, val3);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

  //delay(2000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C\t");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Blynk.virtualWrite(V3,temperature);
  Blynk.virtualWrite(V4,humidity);
  


}

BLYNK_WRITE(V0)
{
  val1 =param.asInt();
  Serial.print("val 1  ");
  Serial.println(val1);
  digitalWrite(relay1,!val1);
  EEPROM.put(1, val1);
  EEPROM.commit();
}



BLYNK_WRITE(V1)
{
  val2 =param.asInt();
  Serial.print("val1 2   ");
  Serial.println(val2);
  digitalWrite(relay2,!val2);
  EEPROM.put(2, val2);
  EEPROM.commit();
}


BLYNK_WRITE(V2)
{
  val3 =param.asInt();
  Serial.print("val1 3   ");
  Serial.println(val3);
  digitalWrite(relay3,!val3);
  EEPROM.put(3, val3);
  EEPROM.commit();
}
