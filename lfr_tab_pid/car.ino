void car(int ls , int rs){
Serial.print("LS :");
Serial.print(ls);
Serial.print("    ");
Serial.print("RS :");
Serial.print(rs);
Serial.println("    ");
if (ls ==0){
  digitalWrite(l1,LOW);
  digitalWrite(l2,LOW);   
}
else if (ls >0){
  digitalWrite(l1,HIGH);
  digitalWrite(l2,LOW);   
}
else if (ls <0){
  digitalWrite(l1,LOW);
  digitalWrite(l2,HIGH);   
}

if (rs ==0){
  digitalWrite(r1,LOW);
  digitalWrite(r2,LOW);   
}
else if (rs >0){
  digitalWrite(r1,HIGH);
  digitalWrite(r2,LOW);   
}
else if (rs <0){
  digitalWrite(r1,LOW);
  digitalWrite(r2,HIGH);
}

if (abs(ls>maxspeed)){
  ls = maxspeed;
}
if (abs(rs>maxspeed)){
  rs = maxspeed;
}
analogWrite(ena,abs(ls));
analogWrite(enb,abs(rs));
}
