String voice;

int led1 = 2;
int led2 = 3;
int led3 = 4;
#include <SD.h>                           //include SD module library
#include <TMRpcm.h> 
TMRpcm tmrpcm;//include speaker control library

#define SD_ChipSelectPin 4

void setup() {
  Serial.begin(9600);  
    tmrpcm.speakerPin = 9;                  //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
  
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    
    return;                               //don't do anything more if not
  }
  
  tmrpcm.setVolume(6);                    //0 to 7. Set volume level
  tmrpcm.play("2.wav"); 
}

void loop() {
  while(Serial.available()) {
    delay(10);
    char c=Serial.read();
    if(c=='#')
    {break; }
    voice += c;
}

if (voice.length() > 0) {
  Serial.println(voice);
  if (voice == "*all")
  {tmrpcm.play("2.wav"); }
  
voice="";
}
}
