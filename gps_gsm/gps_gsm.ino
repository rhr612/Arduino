#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int GPS_RXPin = 8, GPS_TXPin = 7;
static const int GSM_RXPin = 3, GSM_TXPin = 2;
static const uint32_t GPSBaud = 9600;
static const uint32_t GSMBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial GPS(GPS_RXPin, GPS_TXPin);
SoftwareSerial gsm(GSM_RXPin, GSM_TXPin);

void setup(){
  Serial.begin(9600);
  GPS.begin(GPSBaud);
  gsm.begin(GSMBaud);
}

void loop(){
  while (GPS.available() > 0){
    gps.encode(GPS.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}

void call(){
    Serial.println("Initializing..."); 
  delay(1000);

  gsm.println("AT"); //Handshaking with SIM900
  updateSerial();

  gsm.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsm.println("AT+CMGS=\"+8801625473421\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsm.print("hello rhr"); //text content
  updateSerial();
  gsm.write(26);
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
    Serial.write(gsm                                                                         .read());//Forward what Software Serial received to Serial Port
  }
}
