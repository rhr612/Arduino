void linefollow(){
    if(error == 420){
        if(lastsensor == 1){
             car(-80,80);
          }
        else if(lastsensor == 8){
                  car(80,-80);
          }
  }
   else{
  
      if(s1==1 && s2==1 && s3==1 && s4==1 && s5==1 && s6==1 && s7==1 && s8==1){
       delay(100);
       car(0,0);
      }
    
      else{
      p= kp*error;
      d=kd*(error-preverror);
      Nspeed=p+d;
      car(Lspeed -Nspeed,Rspeed+Nspeed);
      preverror=error; 
     }
  }
}
