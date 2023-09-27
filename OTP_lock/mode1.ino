void mode1(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Wellcome to");
  lcd.setCursor(4, 1);
  lcd.print("UGV EEE");
  if(customKey=='#'){
    delay(1000);
    mode=2;
        
  }
}
