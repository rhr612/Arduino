/////////////////////sesnosr//////////////////////////////////////////
int sensor1=A7, sensor2=A6, sensor3=A5, sensor4=A4, sensor5=A3,sensor6=A2,sensor7=A1,sensor8=A0;

int s1,s2,s3,s4,s5,s6,s7,s8;
int sa1,sa2,sa3,sa4,sa5,sa6,sa7,sa8;
int threshhold =3900;
int lastsensor=0;
///////////////////////////////////////////////////////////////////


////////////////////////////motor///////////////////////////////////

int r1=3;
int r2=4;
int l1=9;
int l2=10;
int ena=5;
int enb=6;

int Rspeed=100,Lspeed=100;

int maxspeed=255;
////////////////////////////////////////////////////////////////////
float error,preverror,sums,sumsw,currentposition,Nspeed;
int kp=0.88 ,kd=0.77;
float p,d;
//////////////////////////////////////////////////////////////////


void car();
void linefollow();
void readsensor();
void setup() {
    Serial.begin(9600);
pinMode(sensor1,INPUT);
pinMode(sensor2,INPUT);
pinMode(sensor3,INPUT);
pinMode(sensor4,INPUT);
pinMode(sensor5,INPUT);
pinMode(sensor6,INPUT);
pinMode(sensor7,INPUT);
pinMode(sensor8,INPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(l1,OUTPUT);
pinMode(l2,OUTPUT);
pinMode(ena,OUTPUT);
pinMode(enb,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
readsensor();
//Serial.println(error);
linefollow();

//Serial.print("lastsensor: ");
//Serial.println(lastsensor);

//delay(500);

}
