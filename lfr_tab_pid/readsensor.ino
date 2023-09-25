void readsensor(){
sa1=analogRead(sensor1);
sa2=analogRead(sensor2);
sa3=analogRead(sensor3);
sa4=analogRead(sensor4);
sa5=analogRead(sensor5);
sa6=analogRead(sensor6);
sa7=analogRead(sensor7);
sa8=analogRead(sensor8);

if (sa1>threshhold){
  s1 = 1;
}
else if (sa1<threshhold){
  s1=0;
}

if (sa2>threshhold){
  s2 = 1;
}
else if (sa2<threshhold){
  s2=0;
}

if (sa3>threshhold){
  s3 = 1;
}
else if (sa3<threshhold){
  s3=0;
}

if (sa4>threshhold){
  s4 = 1;
}
else if (sa4<threshhold){
  s4=0;
}

if (sa5>threshhold){
  s5 = 1;
}
else if (sa5<threshhold){
  s5=0;
}

if (sa6>threshhold){
  s6 = 1;
}
else if (sa6<threshhold){
  s6=0;
}

if (sa7>threshhold){
  s7 = 1;
}
else if (sa7<threshhold){
  s7=0;
}

if (sa8>threshhold){
  s8 = 1;
}
else if (sa8<threshhold){
  s8=0;

}

Serial.print(s1);
Serial.print("   ");
Serial.print(s2);
Serial.print("   ");
Serial.print(s3);
Serial.print("   ");
Serial.print(s4);
Serial.print("   ");
Serial.print(s5);
Serial.print("   ");
Serial.print(s6);
Serial.print("   ");
Serial.print(s7);
Serial.print("   ");
Serial.print(s8);
Serial.println("   ");

  //////////set point 45   22.5/////////////////
  
  sums =s1+s2+s3+s4+s5+s6+s7+s8;
  sumsw=(s1*5)+(s2*10)+(s3*15)+(s4*20)+(s5*25)+(s6*30)+(s7*35)+(s8*40);
  currentposition=sumsw/sums;
    
   if(s1==1){
    lastsensor=1;
  }
  else if(s8==1){
    lastsensor=8;
  }

  if(sums==0){
    error=420;
  }
  else{
    error=currentposition-22.5;
}
}
