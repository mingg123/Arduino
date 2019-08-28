/*
 * IRremote: IRrecvDump - dump details of IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 */

#include <IRremote.h>

int RECV_PIN =3;
int ch1= 0;
int num=0;
int prvnum=0;
int a=0;
unsigned long last = millis();

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(ch1,OUTPUT);
   Serial.println("채널을 선택해주세요");
  
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void car_front(){
 
       Serial.println("FRONT");      //시리얼 모니터에 FRONT 문 출력
        digitalWrite(4,HIGH);         // 
      digitalWrite(5,LOW);          //모터 1,2 정방향 회전 (직진)
      digitalWrite(6,HIGH);         //
      digitalWrite(7,LOW);          //
      delay(500);                          //5초간 회전
     digitalWrite(4,LOW);          //
      digitalWrite(5,LOW);          //모터 1,2 정지
      digitalWrite(6,LOW);          //
      digitalWrite(7,LOW);         //
}
void car_back(){
      
      Serial.println("BACK");        //시리얼 모니터에 BACK 문 출력
      digitalWrite(4,LOW);           // 
      digitalWrite(5,HIGH);          //모터 1,2 역방향 회전 (후진)
      digitalWrite(6,LOW);           //
      digitalWrite(7,HIGH);          //
      delay(500);                          //5초간 회전
      digitalWrite(4,LOW);           // 
      digitalWrite(5,LOW);           //모터 1,2 정지
      digitalWrite(6,LOW);           //
      digitalWrite(7,LOW);           //
}
void car_left(){
      Serial.println("LEFT");        //시리얼 모니터에 LEFT 문 출력 
      digitalWrite(4,LOW);           //
      digitalWrite(5,HIGH);           //모터 1 정지 / 모터 2 회전 (좌회전)
      digitalWrite(6,HIGH);          //
      digitalWrite(7,LOW);           //
      delay(500);                            //5초간 회전
      digitalWrite(4,LOW);           //
      digitalWrite(5,LOW);           //모터 1,2 정지
      digitalWrite(6,LOW);           //
      digitalWrite(7,LOW);           //
}
void car_right(){
       Serial.println("RIGHT");        //시리얼 모니터에 RIGHT 문 출력 
      digitalWrite(4,HIGH);           // 
      digitalWrite(5,LOW);            //모터 1 회전 / 모터 2 정지 (우회전)
      digitalWrite(6,LOW);            //
      digitalWrite(7,HIGH);            //
      delay(500);                            //5초간 회전
      digitalWrite(4,LOW);            //
      digitalWrite(5,LOW);            //모터 1,2 정지
      digitalWrite(6,LOW);            //
      digitalWrite(7,LOW);            //
}
void car_stop(){
      digitalWrite(4,LOW);           // 
      digitalWrite(5,LOW);            //모터 1 회전 / 모터 2 정지 (우회전)
      digitalWrite(6,LOW);            //
      digitalWrite(7,LOW);            //
      delay(500);                            //5초간 회전
      digitalWrite(4,LOW);            //
      digitalWrite(5,LOW);            //모터 1,2 정지
      digitalWrite(6,LOW);            //
      digitalWrite(7,LOW);            //
}
void ch1open(int a){
    if(a==1){
    while(1){
     if (irrecv.decode(&results)){
       irrecv.resume();
   if(results.value==0xE0E0807F)  //앞
      {
        car_front();
         Serial.println(results.value, HEX);
       
      }
       if(results.value==0xE0E040BF)  //뒤
      {
        car_back();
         Serial.println(results.value, HEX);
     
      }
        if(results.value==0xE0E020DF)  //왼
      {
        car_left();
         Serial.println(results.value, HEX);

      }
        if(results.value==0xE0E010EF)  //오
      {
        car_right();
         Serial.println(results.value, HEX);
            
      }
          if(results.value==0xE0E0F00F)  //오
      {
         Serial.println(results.value, HEX);
         num++;

         Serial.println("채널을 빠져나갑니다.");
         break;
      }
    }
    }
}
}

void ch2open(int a){
   if(a==2){
   while(1){
     if (irrecv.decode(&results)){
       irrecv.resume();
   if(results.value==0xE0E0807F)  //앞
      {
        car_front();
         Serial.println(results.value, HEX);
      }
       if(results.value==0xE0E040BF)  //뒤
      {
        car_back();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E020DF)  //왼
      {
        car_left();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E010EF)  //오
      {
        car_right();
         Serial.println(results.value, HEX);
      }
          if(results.value==0xE0E0F00F)  //오
      {
         Serial.println(results.value, HEX);
         num++;
         Serial.println("채널을 빠져나갑니다.");
         break;
      }
    }
    }
}
}
void ch3open(int a){
   if(a==3){
  
  
   while(1){
     if (irrecv.decode(&results)){
       irrecv.resume();
   if(results.value==0xE0E0807F)  //앞
      {
        car_front();
         Serial.println(results.value, HEX);
      }
       if(results.value==0xE0E040BF)  //뒤
      {
        car_back();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E020DF)  //왼
      {
        car_left();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E010EF)  //오
      {
        car_right();
         Serial.println(results.value, HEX);
      }
          if(results.value==0xE0E0F00F)  //오
      {
         Serial.println(results.value, HEX);
         num++;
         Serial.println("채널을 빠져나갑니다.");
         break;
      }
    }
    }
}
}
void ch4open(int a){
  if(a==4){
   while(1){
     if (irrecv.decode(&results)){
       irrecv.resume();
   if(results.value==0xE0E0807F)  //앞
      {
        car_front();
         Serial.println(results.value, HEX);
      }
       if(results.value==0xE0E040BF)  //뒤
      {
        car_back();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E020DF)  //왼
      {
        car_left();
         Serial.println(results.value, HEX);
      }
        if(results.value==0xE0E010EF)  //오
      {
        car_right();
         Serial.println(results.value, HEX);
      }
          if(results.value==0xE0E0F00F)  //오
      {
         Serial.println(results.value, HEX);
         num++;
         Serial.println("채널을 빠져나갑니다.");
         break;
      }
    }
    }
}
}

void loop() {
   a++;
   if(a==5)
   {
    a=0; //reset
   }
  if (irrecv.decode(&results)){
    digitalWrite(ch1,HIGH);

    Serial.println(results.value, HEX);
   
 
    //irrecv.resume(); // Receive the next value
    if(num!=prvnum)
    {
      prvnum=num;
      Serial.println(prvnum);
      irrecv.resume();
    }
    
     switch(results.value)
    {
      
       case 0xE0E014EB :    //channel 1
       {
      
        digitalWrite(ch1,LOW);  
        Serial.println("1 channel");
        ch1open(a);
        break;
        }
       
        case 0xE0E015EA :
        {                //channel 2
      
       digitalWrite(ch1,HIGH);
       Serial.println("2 channel");
       ch2open(a);
       break;
        }
        case 0xE0E016E9 : 
        {//channel 3
    
       digitalWrite(ch1,HIGH);
       Serial.println("3 channel");
       ch3open(a);
       break;
        }
        case 0xE0E017E8 :  
        {//channel 4
  
       digitalWrite(ch1,HIGH);
       Serial.println("4 channel");
       ch4open(a);
       break;
 
    }
  
       }
}
}
