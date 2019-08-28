const int BUZZER_PIN = 7;

const int C = 261;    //도
const int D = 294;    //레
const int E = 330;    //미
const int F = 349;    //파
const int G = 392;    //솔
const int A = 440;    //라
const int B = 494;    //시
const int Q = 523; //높은 도
const int S= 0; //쉼표

void setup() {
  pinMode(BUZZER_PIN,OUTPUT);

}

void Do(){
    tone(BUZZER_PIN, C);
 
}
void re(){
    tone(BUZZER_PIN, D);

}
void mi (){
    tone(BUZZER_PIN, E);

}
void pa(){
    tone(BUZZER_PIN, F);

}
void sol(){
    tone(BUZZER_PIN, G);


}
void la(){
    tone(BUZZER_PIN, A);
 
}
void si(){
   
  tone(BUZZER_PIN, B);

}
void upDo(){
    tone(BUZZER_PIN, Q);
  
}
void rest()
{
  tone(BUZZER_PIN, S);
  
}

 
void loop() {
  pa();
  delay(400);
  sol();
  delay(400);
  la();
  delay(1600);
  rest();
  delay(50);
  la();
  delay(800);
  pa();
  delay(400);
  sol();
  delay(400);
  rest();
  delay(50);
  sol();
  delay(1200);
  re();
  delay(400);
  rest();
  delay(50);
  re();
  delay(1200);
  rest();
  delay(100);
  Do();
  delay(400);
  re();
  delay(1200);
  pa();
  delay(400);
  rest();
  delay(50);
  pa();
  delay(400);
    rest();
  delay(50);
  pa();
  delay(800);
  sol();
  delay(400);
  rest();
  delay(50);
  sol();
  delay(800);
  upDo();
  delay(800);
  la();
  delay(400);
  rest();
  delay(50);
  la();
  delay(1200);
  re();
  delay(400);
  rest();
  delay(50);
  re();
  delay(1600);
  
  rest(); 
  delay(1200);
  noTone(BUZZER_PIN);
}
