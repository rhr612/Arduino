
  void send_sms(String x){

  Serial.println("Initializing..."); 
  delay(1000);

  gsm.println("AT"); //Handshaking with SIM900
  updateSerial();

  gsm.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  gsm.println("AT+CMGS=\"+8801759532528\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  gsm.print("Your OTP is : "+ x);
  Serial.print("done");
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
