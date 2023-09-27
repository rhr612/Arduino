void mode3(){
       // Initialize LCD and print
       //
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    if (customKey) {
      // Enter keypress into array and increment counter
      Data += customKey;
      lcd.setCursor(data_count, 1);
      lcd.print(Data[data_count]);
      data_count++;
    }
  
    if(error<3){
        if (data_count == Password_Length) {
          lcd.clear();
      
          if (Data == password) {
            // Correct Password
            lcd.print("Correct");
            // Turn on relay for 5 seconds
            digitalWrite(relay, HIGH);
            delay(5000);
            digitalWrite(relay, LOW);
            mode=1;
          }
          else {
            // Incorrect Password
            lcd.print("Incorrect");
            error+=1;
            delay(1000);
          }
      
          // Clear data and LCD display
          lcd.clear();
          clearData();
        }
       }
      else{
        mode=4;
        lcd.clear();
        lcd.setCursor(7, 0);
        
        lcd.print("3!");
        lcd.setCursor(2, 1);
        lcd.print("Wrong Attemped");
        delay(2000);
        
      }
}
