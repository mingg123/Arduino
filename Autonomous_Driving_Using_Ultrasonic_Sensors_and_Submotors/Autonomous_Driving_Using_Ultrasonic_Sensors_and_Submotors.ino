#include <Servo.h> 
int trigPin = 3;
int echoPin= 2;                                                                                                   
int servoPin = 8;
int direct;
Servo servo; 

int angle = 0; // servo position in degrees 

long duration, distance;    
void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin); 
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);   
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
    /*  digitalWrite(4,LOW);          //
      digitalWrite(5,LOW);          //모터 1,2 정지
      digitalWrite(6,LOW);          //
      digitalWrite(7,LOW);        */  //
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
void developmentdistance(){   //초음파 거리측정
    digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);          
  digitalWrite(trigPin, HIGH);   
  delayMicroseconds(10);       
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 17 / 1000;
  Serial.println(distance);
 
}
void loop()
{
   car_front();

    for(angle = 0; angle <180; angle+=5) 
  { direct=angle;
    servo.write(angle); 
    delay(15); 
   developmentdistance();
        while(distance < 10){   //장애물 감지하면
          car_stop();    //멈추고
          delay(100);
          car_back();   //뒤로
          delay(100);
                 if(direct >=0 && direct <=90)  //왼쪽에 장애물
                       car_right(); // 오른쪽으로
                       delay(100);
                       developmentdistance();
                      if(distance > 10){   //장애물없으면 직진
                        break;
                         }
                  
                  if(direct >90 && direct<=180)  //오른쪽에 장애물잇음
                  {
                          car_left();  //왼쪽
                          delay(100);
                          developmentdistance();
                          if(distance > 10)   //장애물없으면 직진
                          break;
                   }
        }
  }
   
 
     // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle-=5) 
  { direct=angle;
    servo.write(angle); 
    delay(15); 
   developmentdistance();
        while(distance < 10){   //장애물 감지하면
          car_stop();    //멈추고
          delay(100);
          car_back();   //뒤로
          delay(100);
                 if(direct <= 90)  //왼쪽에장애물있음
                  {
                       car_right();   //오른쪽으로 
                       delay(100);
                       developmentdistance();
                      if(distance > 10){   //장애물없으면 직진
                        break;
                         }
                  }
                  if (direct >90)  //오른쪽에 장애물이있음
                  {
                          car_left();   //바꿈
                          delay(100);
                          developmentdistance();
                          if(distance > 10)   //장애물없으면 직진
                          break;
                   }
        }
  }
  }
  
