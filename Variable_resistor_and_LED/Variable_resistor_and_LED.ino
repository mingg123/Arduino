/* 출처 : 아두이노 상상을 스케치하다*/
int LED_pins[] = {0,1,2,3,4,5,6,7};//array를 통해 8,9,10,11,12 번의 핀번호를 순차적으로 배열합니다.
int currentVoltage = 0;//현재 전압의 상태를 확인합니다.
int previousVoltage = 0;//이전 전압의 상태를 확입합니다.
void setup()
{
  for(int i = 0; i < sizeof(LED_pins) / sizeof(int); i++){
    pinMode(LED_pins[i],OUTPUT);
  }
  Serial.begin(9600);
}
void loop()
{
  int analogIn = analogRead(A0);
  currentVoltage = map(analogIn , 0, 1023, 0, 8);  // 아날로그인 0~1023을 0~8로 범위를 알아서 나눔
  if(currentVoltage != previousVoltage){
    previousVoltage = currentVoltage;
    for(int i =0; i < currentVoltage; i++){  //킨다
      digitalWrite(LED_pins[i],LOW);
    }
    for(int i = currentVoltage; i < 8; i++){  //나머지끈다
      digitalWrite(LED_pins[i],HIGH);
    }
  }
  Serial.println(analogIn);
}
