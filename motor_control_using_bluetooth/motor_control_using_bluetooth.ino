#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
 
int blueTx=2;   //Tx (보내는핀 설정)
int blueRx=3;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString=""; //받는 문자열
 
void setup() {
  Serial.begin(9600);   //시리얼모니터 
  mySerial.begin(9600); //블루투스 시리얼 개방
 // pinMode(4, OUTPUT);  //Pin 4을 OUTPUT으로 설정 (LED ON/OFF)
  pinMode(4, OUTPUT);   //모터드라이버 모터4핀
  pinMode(5, OUTPUT);   //모터드라이버 모터3핀
  pinMode(6, OUTPUT);   //모터드라이버 모터2핀
  pinMode(7, OUTPUT);   //모터드라이버 모터1핀

}
void car_front(){
       // Serial.println("FRONT");      //시리얼 모니터에 FRONT 문 출력
        digitalWrite(4,HIGH);         // 
      digitalWrite(5,LOW);          //모터 1,2 정방향 회전 (직진)
      digitalWrite(6,HIGH);         //
      digitalWrite(7,LOW);          //
      delay(500);                          //5초간 회전
      digitalWrite(4,LOW);          //
      digitalWrite(5,LOW);          //모터 1,2 정지
      digitalWrite(6,LOW);          //
      digitalWrite(7,LOW);          //
}
void car_back(){
      
      //Serial.println("BACK");        //시리얼 모니터에 BACK 문 출력
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
   // Serial.println("LEFT");        //시리얼 모니터에 LEFT 문 출력 
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
      //  Serial.println("RIGHT");        //시리얼 모니터에 RIGHT 문 출력 
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

 
void loop() {
  while(mySerial.available())  //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString+=myChar;   //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  if(!myString.equals(""))  //myString 값이 있다면
  {
    Serial.println("input value: "+myString); //시리얼모니터에 myString값 출력
 /*
      if(myString=="on0")  //myString 값이 'on0' 이라면
      {
        digitalWrite(4, LOW); //LED ON
      } else {
        digitalWrite(4, HIGH);  //LED OFF
      }
      */
      if(myString=="front")
      {
        car_front();
      }
    if(myString=="back")
      {
        car_back();
      }
        if(myString=="right")
      {
            car_right();
      }
        if(myString=="left")
      {
        car_left();
      }
     
    myString="";  //myString 변수값 초기화
  }
}
