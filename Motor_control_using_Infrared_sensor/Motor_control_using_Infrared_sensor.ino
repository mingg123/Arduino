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

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
    pinMode(7, OUTPUT);   //모터드라이버 모터4핀
  pinMode(8, OUTPUT);   //모터드라이버 모터3핀
  pinMode(9, OUTPUT);   //모터드라이버 모터2핀
  pinMode(10, OUTPUT);   //모터드라이버 모터1핀
}

// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void car_front(){
       // Serial.println("FRONT");      //시리얼 모니터에 FRONT 문 출력
        digitalWrite(7,HIGH);         // 
      digitalWrite(8,LOW);          //모터 1,2 정방향 회전 (직진)
      digitalWrite(9,HIGH);         //
      digitalWrite(10,LOW);          //
      delay(500);                          //5초간 회전
      digitalWrite(7,LOW);          //
      digitalWrite(8,LOW);          //모터 1,2 정지
      digitalWrite(9,LOW);          //
      digitalWrite(10,LOW);          //
}
void car_back(){
      
      //Serial.println("BACK");        //시리얼 모니터에 BACK 문 출력
      digitalWrite(7,LOW);           // 
      digitalWrite(8,HIGH);          //모터 1,2 역방향 회전 (후진)
      digitalWrite(9,LOW);           //
      digitalWrite(10,HIGH);          //
      delay(500);                          //5초간 회전
      digitalWrite(7,LOW);           // 
      digitalWrite(8,LOW);           //모터 1,2 정지
      digitalWrite(9,LOW);           //
      digitalWrite(10,LOW);           //
}
void car_left(){
   // Serial.println("LEFT");        //시리얼 모니터에 LEFT 문 출력 
      digitalWrite(7,LOW);           //
      digitalWrite(8,HIGH);           //모터 1 정지 / 모터 2 회전 (좌회전)
      digitalWrite(9,HIGH);          //
      digitalWrite(10,LOW);           //
      delay(500);                            //5초간 회전
      digitalWrite(7,LOW);           //
      digitalWrite(8,LOW);           //모터 1,2 정지
      digitalWrite(9,LOW);           //
      digitalWrite(10,LOW);           //
}
void car_right(){
      //  Serial.println("RIGHT");        //시리얼 모니터에 RIGHT 문 출력 
      digitalWrite(7,HIGH);           // 
      digitalWrite(8,LOW);            //모터 1 회전 / 모터 2 정지 (우회전)
      digitalWrite(9,LOW);            //
      digitalWrite(10,HIGH);            //
      delay(500);                            //5초간 회전
      digitalWrite(7,LOW);            //
      digitalWrite(8,LOW);            //모터 1,2 정지
      digitalWrite(9,LOW);            //
      digitalWrite(10,LOW);            //
}
void car_stop(){
      digitalWrite(7,LOW);           // 
      digitalWrite(8,LOW);            //모터 1 회전 / 모터 2 정지 (우회전)
      digitalWrite(9,LOW);            //
      digitalWrite(10,LOW);            //
      delay(500);                            //5초간 회전
      digitalWrite(7,LOW);            //
      digitalWrite(8,LOW);            //모터 1,2 정지
      digitalWrite(9,LOW);            //
      digitalWrite(10,LOW);            //
}



void loop() {
  if (irrecv.decode(&results)) {
   // Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  
    switch(results.value)
  {
    case 0xFF18E7 : //2
    car_front();
    Serial.println("front");
    break;
    case 0xFF10EF: //4
    car_left();
        Serial.println("left");
    break;
    case 0xFF5AA5: //6
    car_right();
        Serial.println("right");
    break;
    case 0xFF4AB5: //8
   car_back();
        Serial.println("back");
    break;
    case 0xFF38C7 :  //5 
    car_stop();
        Serial.println("stop");
    break;
    
  }
}
}
