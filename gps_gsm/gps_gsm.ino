

#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
static const int GSM_RXPin = 3, GSM_TXPin = 2;
SoftwareSerial gsm(GSM_RXPin, GSM_TXPin);


#include <TinyGPS++.h>
static const int GPS_RXPin = 8, GPS_TXPin = 7;
TinyGPSPlus gps;
SoftwareSerial GPS(GPS_RXPin, GPS_TXPin);


String link,sum;
double Latitude,Longitude;
char val;


void setup(){
  link="http://maps.google.com/maps?q=loc:";
  gsm.begin(9600);
  GPS.begin(9600);
  Serial.begin(9600);
  
  delay(1000);
  
 
}

void loop(){

 if(val!='1'){
  while (Serial.available() > 0)
  {
  val = Serial.read();
  Serial.println(val);
  }
  
  while (GPS.available() > 0){
    gps.encode(GPS.read());
    if (gps.location.isUpdated()){
      
      Serial.print("Latitude= "); 
      Latitude=gps.location.lat();
      Serial.print(Latitude,6);
      Serial.print(" Longitude= "); 
      Longitude=gps.location.lng();
      Serial.println(Longitude,6);
     // Serial.println(GPS.available());
      delay(500);
      sum="Accident detected!!!! The location is :\r";
        sum+=link;
        sum+=String(Latitude,10)+","+String(Longitude,10);  
        
    }
    }}
  

else if (val=='1'){
        
        Serial.println(sum);
        //delay(1000);
        Serial.println("Initializing..."); 
 // delay(1000);

  gsm.println("AT"); //Handshaking with SIM900
  updateSerial();

  gsm.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsm.println("AT+CMGS=\"+8801625473421\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsm.print(sum); //text content
  Serial.print("done");
  updateSerial();
  gsm.write(26);
        //delay(1000);
        val='0';
      }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    gsm.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(gsm.available()) 
  {
    Serial.write(gsm.read());//Forward what Software Serial received to Serial Port
  }
}
