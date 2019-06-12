int motor = 11;
int MOTOR_STATUS = 0;
int IR = 10;

int lys1 = 3;
int lys2 = 5;

int grontLys = 6;
int rodtLys = 2;
int gultLys = 4;

boolean hartbeat = false;

#include <IRremote.h>

int RECV_PIN = IR;  //Connect the receiver to pin 11
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Starting the receiver
  
  pinMode(lys1,OUTPUT);
  pinMode(lys2,OUTPUT);
  
  pinMode(grontLys, OUTPUT);
  pinMode(rodtLys, OUTPUT);
  pinMode(gultLys, OUTPUT);
  
  digitalWrite(rodtLys,HIGH);
  delay(1000);
  digitalWrite(rodtLys,LOW);
  digitalWrite(lys1,HIGH);
  delay(1000);
  digitalWrite(lys1,LOW);
  digitalWrite(gultLys,HIGH);
  delay(1000);
  digitalWrite(gultLys,LOW);
  digitalWrite(lys2,HIGH);
  delay(1000);
  digitalWrite(lys2,LOW);
  digitalWrite(grontLys,HIGH);
  delay(1000);
  digitalWrite(grontLys,LOW);
  
  pinMode(motor,OUTPUT);
  digitalWrite(motor, HIGH);
  delay(1000);
  digitalWrite(motor, LOW);
}
void loop() {
  
  if (irrecv.decode(&results)) {
    switch (results.value)  {
      case 0xFF6897:
        Serial.println("1");
        skytelys(1);
        break;
      case 0xFF9867:
        Serial.println("2");
        skytelys(3);
        break;
      case 0xFFB04F:
        Serial.println("3");
        skytelys(6);
        break;
      case 0xFF30CF:
        Serial.println("4");
        break;
      case 0xFF18E7:
        Serial.println("5");
        break;
      case 0xFF7A85:
        Serial.println("6");
        break;
      case 0xFF10EF:
        Serial.println("7");
        break;
      case 0xFF38C7:
        Serial.println("8");
        break;
      case 0xFF5AA5:
        Serial.println("9");
        break;
      case 0xFF4AB5:
        Serial.println("0 : klikk");
        lyd(1);
        break;
      case 0xFF42BD:
        Serial.println("# : SHAKE");
        SHAKE(1000,255);
        Serial.println("SHAKE");
        break;
      case 0xFF52AD:
        Serial.println("* : SHAKE Med");
        SHAKE(1000, 255);
        break;
      case 0xFF02FD:
        Serial.println("OK");
        lyd(1);
        break;
      case 0xFF22DD:
        Serial.println("RIGHT: : SHORT _BLINK");
        //Korte blink
        blunk(200);
        break;
      case 0xFF629D:
        Serial.println("UP : MOTOR_MAX");
        MOTOR(255);
        break;
      case 0xFFC23D:
        Serial.println("LEFT? : LONG_BLINK");
        //langBlink
        blunk(500);
        break;
      case 0xFFA857:
        Serial.println("DOWN : MOTOR_OFF");
        analogWrite(motor, 0);
        break;        
    }
  irrecv.resume(); // Receive the next value
  }
}

void blunk(int x){
  int tid = millis();
  int sjekktid = tid + x;
  lys(HIGH);
  while(sjekktid>tid){
    tid = millis();
  }
  lys(LOW);
}

void SHAKE(int tid, int styrke){
  Serial.println("SHAKE");
  MOTOR(styrke);
  int start = millis();
  int sjekktid = millis();
  Serial.println("SHAKE");
  while(start + tid>sjekktid){
    sjekktid = millis();
  }
  Serial.println("SHAKE");
  MOTOR(0);
}

void lys(int x){
  digitalWrite(lys1,x);
  digitalWrite(lys2,x);
}

void skytelys(int piler){

    lyd(0);
    lyd(0);
    
    int long tid = millis() + 10000;
    while(tid > millis()){
      digitalWrite(rodtLys, HIGH);
  
    }

    tid = millis() + piler * 30000 - piler * 5000;
    lyd(0);
    
    while(tid > millis()){
      digitalWrite(grontLys, HIGH);
      digitalWrite(gultLys, LOW);
      digitalWrite(rodtLys, LOW);
    }
    
    tid = millis() + piler * 5000;
    int rist = millis ();
    
    while(tid > millis()){
      digitalWrite(grontLys, LOW);
      digitalWrite(gultLys, HIGH);
      digitalWrite(rodtLys, LOW);
      if (millis() > rist){
        rist = millis() + 500;
        SHAKE(300, 255);
      }
    }
    
    lyd(0);
    lyd(0);
    lyd(0);
    
    digitalWrite(grontLys, LOW);
    digitalWrite(gultLys, LOW);
    digitalWrite(rodtLys, HIGH);

    delay(1000);
  
    digitalWrite(grontLys, LOW);
    digitalWrite(gultLys, LOW);
    digitalWrite(rodtLys, LOW);
}

void lyd(int x){
  String stringAaSende = "PAS" + String(x);
  Serial.println(stringAaSende);
  delay(1000);
}
