
int trigpin = 3;
int echopin = 2;
int s1,s2;
int m1=8;
int m2=9;
int m3=11;
int m4=10;


long duration,distance;

void  setup(){
  Serial.begin(9600);

  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  }

void loop(){
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 duration= pulseIn(echopin,HIGH);
 distance=duration*0.034/2;

 s1=digitalRead(A0);
 s2=digitalRead(A1);
 Serial.print(distance);
 Serial.print("      ");
 Serial.print(s1);
 Serial.print("      ");
 Serial.println(s2);
 //delay(10);

  if(distance>19){
  digitalWrite(m1,HIGH);
  digitalWrite(m2,LOW);
  digitalWrite(m3,HIGH);
  digitalWrite(m4,LOW);
  }



    else if(distance<19 && s1==1 && s2==1){
          digitalWrite(m1,LOW);
          digitalWrite(m2,HIGH);
          digitalWrite(m3,HIGH);
          digitalWrite(m4,LOW);
  }

    else if(distance<19 && s1==1 && s2==0){
          digitalWrite(m1,HIGH);
          digitalWrite(m2,LOW);
          digitalWrite(m3,LOW);
          digitalWrite(m4,HIGH);
  }
 else if(distance<19 && s1==0 && s2==1){
          digitalWrite(m1,LOW);
          digitalWrite(m2,HIGH);
          digitalWrite(m3,HIGH);
          digitalWrite(m4,LOW);
  }

  else if(distance<19 && s1==0 && s2==0){
          digitalWrite(m1,LOW);
          digitalWrite(m2,HIGH);
          digitalWrite(m3,HIGH);
          digitalWrite(m4,LOW);
  }

      else if(distance<19 && s1==0 && s2==0){
          digitalWrite(m1,LOW);
          digitalWrite(m2,HIGH);
          digitalWrite(m3,LOW);
          digitalWrite(m4,HIGH);
  }

 
 }

 
