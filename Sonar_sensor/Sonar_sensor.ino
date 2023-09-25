
int trigpin = 3;
int echopin = 2;

long duration,distance;

void  setup(){
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);

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
 
 }

 
