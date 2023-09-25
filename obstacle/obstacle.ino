
int trigpin = 3;
int echopin = 2;

int RM1=10;      // right motor
int RM2=11 ;      // right motor
int LM1=8;      // left motor
int LM2=9;      // left motor

long duration,distance;

void  setup(){
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);

  }

void loop(){
 digitalWrite(trigpin,LOW);
 delayMicroseconds(2);
 digitalWrite(trigpin,HIGH);
 delayMicroseconds(10);
 duration= pulseIn(echopin,HIGH);
 distance=duration*0.034/2;
 Serial.println(distance);
 delay(10);

 if(distance<15){
  digitalWrite(LM1,LOW);
  digitalWrite(LM2,HIGH);
  digitalWrite(RM1,LOW);
  digitalWrite(RM2,LOW);
  delay(800);
 }

 else{
  digitalWrite(LM1,HIGH);
  digitalWrite(LM2,LOW);
  digitalWrite(RM1,HIGH);
  digitalWrite(RM2,LOW);
 }
 
 }

 
