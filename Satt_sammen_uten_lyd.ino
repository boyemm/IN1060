int motor = 11;
int MOTOR_STATUS = 0;
int IR = 10;

int lys1 = 3;
int lys2 = 5;

int grontLys = 6;
int rodtLys = 2;
int gultLys = 4;

int long SKYTESTART = 0;

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
        //Spiller av lyd
        break;
      case 0xFF9867:
        Serial.println("2");
        //Spiller av lyd
        break;
      case 0xFFB04F:
        Serial.println("3");
        //Spiller av lyd
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
        Serial.println("0 : START SKYTEPROGRAM");
        SKYTESTART = millis();
        break;
      case 0xFF42BD:
        Serial.println("# : SHAKE");
        SHAKE(1000,200);
        break;
      case 0xFF52AD:
        //Skrur seg ikke av
        Serial.println("* : SHAKE");
        SHAKE(1000,100);
        break;
      case 0xFF02FD:
        Serial.println("OK : MOTOR_MEDIUM");
        MOTOR(150);
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

void MOTOR(int NEWVALUE){
  if (MOTOR_STATUS > 0){
    analogWrite(motor, 0);
  }
  MOTOR_STATUS = NEWVALUE;
  analogWrite(motor, MOTOR_STATUS);
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

void skytelys(){
  //Lydeffekter ? først to bip 10 sek før skyting
  //              så et bip for starte skyting
  //              sist tre bip for å avslutte skyting
  if (SKYTESTART + 200000 > millis()){
    digitalWrite(grontLys, HIGH);
    digitalWrite(gultLys, LOW);
    digitalWrite(rodtLys, LOW);
  }
  else if(SKYTESTART + 240000 > millis()){
    digitalWrite(grontLys, LOW);
    digitalWrite(gultLys, HIGH);
    digitalWrite(rodtLys, LOW);
  }
  else if (SKYTESTART + 300000 > millis()){
    digitalWrite(grontLys, LOW);
    digitalWrite(gultLys, LOW);
    digitalWrite(rodtLys, HIGH);
  }
  else{
    digitalWrite(grontLys, LOW);
    digitalWrite(gultLys, LOW);
    digitalWrite(rodtLys, LOW);
  }
}

