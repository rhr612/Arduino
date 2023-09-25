int a,b,c,d,e;
int minValues[5], maxValues[5], threshhold,maxi=0,mini=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//calibrate();
}

void loop() {
  // put your main code here, to run repeatedly:
a=analogRead(1);
b=analogRead(3);
c=analogRead(5);
d=analogRead(7);
e=analogRead(9);

Serial.print(a);
Serial.print("   ");
Serial.print(b);
Serial.print("   ");
Serial.print(c);
Serial.print("   ");
Serial.print(d);
Serial.print("   ");
Serial.print(e);
Serial.print("   ");
Serial.print("thresh");
Serial.print(threshhold);
    Serial.println("   ");
}
