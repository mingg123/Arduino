#include <Servo.h>

// debug 관련 설정
//#define DEBUG               // DEBUG모드 해제시에는 이 줄을 주석처리, 시리얼 모니터는 "새 줄" 선택
unsigned long debug_time;
boolean debug_driving_status = false;

// Pin map
#define LIGHT    13  // Light 제어 핀
#define LED      13  // LED 제어 핀
#define M_PWM    5   // DC모터 PWM 핀
#define M_DIR1   7   // DC모터 DIR1 핀
#define M_DIR2   8   // DC모터 DIR2 핀

#define M2_PWM    6   // DC모터2 PWM 핀
#define M2_DIR1   11   // DC모터2 DIR1 핀
#define M2_DIR2   12   // DC모터2 DIR2 핀

#define SERVO    9   // 서보모터 핀
#define BUZZER   3   // 버저 핀
#define BATTERY  A0  // 배터리 체크 핀

#define FC_TRIG 13   // 전방 초음파 센서 TRIG 핀
#define FC_ECHO 10  // 전방 초음파 센서 ECHO 핀
#define FL_TRIG A4  // 전방좌측 초음파 센서 TRIG 핀
#define FL_ECHO A3  // 전방좌측 초음파 센서 ECHO 핀
#define FR_TRIG 3   // 전방우측 초음파 센서 TRIG 핀
#define FR_ECHO 4   // 전방우측 초음파 센서 ECHO 핀
#define L_TRIG  A2  // 좌측 초음파 센서 TRIG 핀
#define L_ECHO  A1  // 좌측 초음파 센서 ECHO 핀
#define R_TRIG  2   // 우측 초음파 센서 TRIG 핀
#define R_ECHO  A5  // 우측 초음파 센서 ECHO 핀

#define MAX_DISTANCE  2000 // 초음파 센서의 최대 감지거리

// 자동차 튜닝 파라미터
int servo_dir = 1; // 서보 회전 방향(동일: 1, 반대:-1)
int motor_dir = 1; // 모터 회전 방향(동일:1, 반대:-1)
int angle_limit = 50; // 서보 모터 회전 제한 각 (단위: 도)
int angle_offset = 0; // 서보 모터 중앙각 오프셋 (단위: 도)
int max_rc_pwm = 255; // RC조종 모터 최대 출력 (0 ~ 255)
int min_rc_pwm = 110; // RC조종 모터 최소 출력 (0 ~ 255)
int punch_pwm = 180; // 정지 마찰력 극복 출력 (0 ~ 255)
int punch_time = 50; // 정지 마찰력 극복 시간 (단위 msec)
int stop_time = 30; // 전진후진 전환 시간 (단위 msec)
int melody_tempo = 3500; // 멜로디 연주 속도
int melody_num = 41; // 멜로디 음 개수
int battery_cell = 2; // 배터리 셀 개수
float voltage_error = 1.08; // 전압 오차 (1이 오차 없음)

// 자율주행 튜닝 파라미터
int max_ai_pwm = 180; // 자율주행 모터 최대 출력 (0 ~ 255)
int min_ai_pwm = 80; // 자율주행 모터 최소 출력 (0 ~ 255)
int center_detect = 200; // 전방 감지 거리 (단위: mm)
int center_start = 160; // 전방 출발 거리 (단위: mm)
int center_stop1 = 80; // 전방 멈춤 거리 (단위: mm)
int center_stop2 =120; // 전방 멈춤 거리 (단위: mm)
int diagonal_detect = 80; // 대각 감지 거리 (단위: mm)
int diagonal_start = 120; // 대각 출발 거리 (단위: mm)
int diagonal_stop = 180; // 대각 멈춤 거리 (단위: mm)
int side_detect = 250; // 좌우 감지 거리 (단위: mm)
int side_start = 160; // 좌우 조향 시작 거리 (단위: mm)
int side_stop = 50; // 좌우 조향 끝 거리 (단위: mm)
float steering_gain = 1.5; // 좌우 조향 증폭상수


Servo servo;
float cur_steering;
float cur_speed;
float max_pwm;
float min_pwm;
bool sound = false;
bool autoDriving = false;
int melody_index = 0;
unsigned long melody_time;
unsigned long battery_time;
unsigned long rc_time;
float f_center; // 초음파 센서의 거리를 mm 단위로 측정
float f_left;
float f_right;
float left;
float right;
float b_center;

// 초음파 거리측정
float GetDistance(int trig, int echo)
{ 
    digitalWrite(trig, LOW);
    delayMicroseconds(4);
    digitalWrite(trig, HIGH);
    delayMicroseconds(20);
    digitalWrite(trig, LOW);
    
    unsigned long duration = pulseIn(echo, HIGH, 5000);
    if(duration == 0)
        return MAX_DISTANCE;
    else
        return duration * 0.17;     // 음속 340m/s
}

// 앞바퀴 조향 (-1~1까지 값)
void SetSteering(float steering)
{
    cur_steering = constrain(steering, -1, 1);
    
    float angle = cur_steering * angle_limit;
    if(servo_dir < 0)
        angle = -angle;
    
    int servoAngle = angle + 90;
    if(servo_dir < 0)
        servoAngle -= angle_offset;
    else
        servoAngle += angle_offset;
    servoAngle = constrain(servoAngle, 0, 180);
    
    servo.write(servoAngle);
}

// 뒷바퀴 모터회전
void SetSpeed(float speed)
{
    
    speed = constrain(speed, -1, 1);

    if((cur_speed * speed < 0) // 움직이는 중 반대 방향 명령이거나
        || (cur_speed != 0 && speed == 0)) // 움직이다가 정지라면
    {
        cur_speed = 0;
        digitalWrite(M_PWM, HIGH);
        digitalWrite(M_DIR1, LOW);
        digitalWrite(M_DIR2, LOW);

        digitalWrite(M2_PWM, HIGH);
        digitalWrite(M2_DIR1, LOW);
        digitalWrite(M2_DIR2, LOW);

        
        if(stop_time > 0) 
          delay(stop_time);
    }

    if(cur_speed == 0 && speed != 0) // 정지상태에서 출발이라면
    {
        if(punch_time > 0)
        {
            if(speed * motor_dir > 0)
            {
                analogWrite(M_PWM, punch_pwm);
                digitalWrite(M_DIR1, HIGH);
                digitalWrite(M_DIR2, LOW);

                analogWrite(M2_PWM, punch_pwm);
                digitalWrite(M2_DIR1, HIGH);
                digitalWrite(M2_DIR2, LOW);
            }
            else if(speed * motor_dir < 0)
            {
                analogWrite(M_PWM, punch_pwm);
                digitalWrite(M_DIR1, LOW);
                digitalWrite(M_DIR2, HIGH);

                analogWrite(M2_PWM, punch_pwm);
                digitalWrite(M2_DIR1, LOW);
                digitalWrite(M2_DIR2, HIGH);
            }
            
            delay(punch_time);
        }
    }

    if(speed != 0) // 명령이 정지가 아니라면
    {
        int pwm = abs(speed) * (max_pwm - min_pwm) + min_pwm;           // 0 ~ 255로 변환
        if(speed * motor_dir > 0)
        {
            analogWrite(M_PWM, pwm);
            digitalWrite(M_DIR1, HIGH);
            digitalWrite(M_DIR2, LOW);

            analogWrite(M2_PWM, pwm);
            digitalWrite(M2_DIR1, HIGH);
            digitalWrite(M2_DIR2, LOW);
        }
        else if(speed * motor_dir < 0)
        {
            analogWrite(M_PWM, pwm);
            digitalWrite(M_DIR1, LOW);
            digitalWrite(M_DIR2, HIGH);

            analogWrite(M2_PWM, pwm);
            digitalWrite(M2_DIR1, LOW);
            digitalWrite(M2_DIR2, HIGH);
        }
    }

    cur_speed = speed;
}


void setup()
{
    max_pwm = max_rc_pwm;
    min_pwm = min_rc_pwm;
    
    servo.attach(SERVO);    
    pinMode(M_PWM, OUTPUT);
    pinMode(M_DIR1, OUTPUT);
    pinMode(M_DIR2, OUTPUT);

    pinMode(M2_PWM, OUTPUT);
    pinMode(M2_DIR1, OUTPUT);
    pinMode(M2_DIR2, OUTPUT);
    
    pinMode(LIGHT, OUTPUT);
    pinMode(LED, OUTPUT);
    pinMode(FC_TRIG, OUTPUT);
    pinMode(FC_ECHO, INPUT);
    pinMode(FL_TRIG, OUTPUT);
    pinMode(FL_ECHO, INPUT);
    pinMode(FR_TRIG, OUTPUT);
    pinMode(FR_ECHO, INPUT);
    //pinMode(BC_TRIG, OUTPUT);
    //pinMode(BC_ECHO, INPUT);
    pinMode(L_TRIG, OUTPUT);
    pinMode(L_ECHO, INPUT);
    pinMode(R_TRIG, OUTPUT);
    pinMode(R_ECHO, INPUT);
    
    digitalWrite(LIGHT, LOW);
    SetSpeed(0);
    
    //Serial.begin(9600);
    Serial.begin(9600);
    
    battery_time = millis();
    debug_time = millis(); 

    #ifdef DEBUG        
        Serial.print("FC");Serial.print("\t");
        Serial.print("FL");Serial.print("\t");
        Serial.print("FR");Serial.print("\t");
        Serial.print("L");Serial.print("\t");
        Serial.print("R");Serial.print("\t");
        Serial.print("STEERING");Serial.print("\t");
        Serial.print("SPEED");Serial.println();
        //Serial.println("-----------------------------");
    #endif
}

void loop()
{    
    // 전진
    float compute_speed=0.2;
    float compute_steering = 0;
    
    f_center = GetDistance(FC_TRIG, FC_ECHO);
    f_right = GetDistance(FR_TRIG, FR_ECHO);
    f_left = GetDistance(FL_TRIG, FL_ECHO);
    left= GetDistance(L_TRIG, L_ECHO);
    right=GetDistance(R_TRIG, R_ECHO);
    Serial.println(f_left);
    if(f_center<=center_stop1)   //전방에 안전거리 1이내에 물체가 있으면
    {
           
            compute_speed=-0.5; // 후진
            if (f_left > f_right) 
            {
                // 우측으로 후진
                compute_steering = 1;  //조향각 우측으로 조정
            }
            else
            {
              // 좌측으로 후진
                compute_steering = -1;
            }
    }
    
    // 세개의 초음파중 하나라도 안전거리를 지키지 않을 경우
    else if(f_center <= center_stop2 || f_left <= diagonal_stop || f_right <= diagonal_stop)
        {
          if(f_center>=center_stop1)   //전방에 안전거리에 아무것도 없을때 
          {
           if (f_left > f_right) 
            {
                // 좌측으로 전진
                compute_steering = -1;
            }
            else if(f_left < f_right) 
            {
              // 우측으로 전진
                compute_steering = 1;
            }
            
          }
        }

     // 대각왼쪽 or 대각 오른쪽 센서 중 하나라도 감지될 경우
     else if(f_left <= diagonal_detect || f_right <= diagonal_detect)
     {
        // 전방에 감지 안될 경우
        if(f_center > center_detect)
        {
                // 대각 좌측 감지된 경우
                if(f_left < f_right)
                {
                    // 우측으로 최대 조향
                   compute_steering = 1;
                }
                // 대각 우측 감지된 경우
               else if(f_right < f_left)
                {
                    // 좌측으로 최대 조향
                    compute_steering = -1;
                }
            }
     }
      else if(f_center <= center_stop1+ &&( f_left <= diagonal_detect+20 || f_right <= diagonal_detect+20)) //전방에 감지되고, 측방에 둘중 하나라도 무조건 감지될때
     { 
        compute_speed=-1;  //후진
  
            if (left > right) 
            {
                // 우측으로 후진
                compute_steering = 1;
            }
            else
            {
              // 좌측으로 후진
                compute_steering = -1;
            }
     }
    
     SetSteering(compute_steering);
     SetSpeed(compute_speed);
}
