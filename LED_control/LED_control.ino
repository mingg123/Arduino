

#define LED_Buttionout0 0
#define LED_Buttionout1 1
#define LED_Buttionout2 2
#define LED_Buttionout3 3
#define LED_Buttionout4 4
#define LED_Buttionout5 5
#define LED_Buttionout6 6
#define LED_Buttionout7 7

void setup()
{
  pinMode(LED_Buttionout0,OUTPUT);
  pinMode(LED_Buttionout1,OUTPUT);
  pinMode(LED_Buttionout2,OUTPUT);
  pinMode(LED_Buttionout3,OUTPUT);
  pinMode(LED_Buttionout4,OUTPUT);
  pinMode(LED_Buttionout5,OUTPUT);
  pinMode(LED_Buttionout6,OUTPUT);
  pinMode(LED_Buttionout7,OUTPUT);
  
}


void loop(){
   digitalWrite(LED_Buttionout0,LOW);
   digitalWrite(LED_Buttionout1,HIGH);
   digitalWrite(LED_Buttionout2,LOW);
   digitalWrite(LED_Buttionout3,HIGH);
   digitalWrite(LED_Buttionout4,LOW);
   digitalWrite(LED_Buttionout5,HIGH);
   digitalWrite(LED_Buttionout6,LOW);
   digitalWrite(LED_Buttionout7,HIGH); 

   delay(1000);
   digitalWrite(LED_Buttionout0,HIGH);
   digitalWrite(LED_Buttionout1,LOW);
   digitalWrite(LED_Buttionout2,HIGH);
   digitalWrite(LED_Buttionout3,LOW);
   digitalWrite(LED_Buttionout4,HIGH);
   digitalWrite(LED_Buttionout5,LOW);
   digitalWrite(LED_Buttionout6,HIGH);
   digitalWrite(LED_Buttionout7,LOW); 
    delay(1000);
   
}
