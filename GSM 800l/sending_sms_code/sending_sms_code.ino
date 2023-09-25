#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial gsm(3, 2); //SIM900 Tx & Rx is connected to Arduino #7 & #8

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM900
  gsm.begin(9600);

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

void loop()
{
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
