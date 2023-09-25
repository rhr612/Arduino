void calibrate()
{
  for ( int i = 1; i < 10; i=i+2)
  {
    minValues[i] = analogRead(i);
    maxValues[i] = analogRead(i);
  }
  
  for (int i = 0; i < 3000; i++)
  {
//    motor1.drive(50);
//    motor2.drive(-50);

    for ( int i = 1; i < 10; i=i+2)
    {
      if (analogRead(i) < minValues[i])
      {
        minValues[i] = analogRead(i);
      }
      if (analogRead(i) > maxValues[i])
      {
        maxValues[i] = analogRead(i);
      }
    }
  }

  for ( int i = 1; i < 10; i=i+2)
  {
    mini=mini+minValues[i];
    maxi=maxi+maxValues[i];
    
  }
  //Serial.println();
  int minavg=mini/5;
  int maxavg=maxi/5;
  threshhold=(minavg+maxavg)/2;
  
//  motor1.drive(0);
//  motor2.drive(0);
}
