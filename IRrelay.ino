#include <IRremote.h>

int RECV_PIN = 11;  //Connect the IR-receiver to pin 11
IRrecv irrecv(RECV_PIN);
decode_results results;
boolean status[8];
boolean tmp_status;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Starting the IR-receiver
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    switch (results.value)  {

      case 0xFF6897:  // Button 1 pressed
      Serial.println("1");
      status[0] = !status[0];  // Toggle the status bit for relay 1
      digitalWrite(2, status[0]);  // Toggle relay 1
      break;

    case 0xFF9867:  // Button 2 pressed
      Serial.println("2");
      status[1] = !status[1];
      digitalWrite(3, status[1]);
      break;

    case 0xFFB04F:   // Button 3 pressed...
      Serial.println("3");
      status[2] = !status[2];
      digitalWrite(4, status[2]);
      break;

    case 0xFF30CF:
      Serial.println("4");
      status[3] = !status[3];
      digitalWrite(5, status[3]);
      break;

    case 0xFF18E7:
      Serial.println("5");
      status[4] = !status[4];
      digitalWrite(6, status[4]);
      break;

    case 0xFF7A85:
      Serial.println("6");
      status[5] = !status[5];
      digitalWrite(7, status[5]);
      break;

    case 0xFF10EF:
      Serial.println("7");
      status[6] = !status[6];
      digitalWrite(8, status[6]);
      break;

    case 0xFF38C7:
      Serial.println("8");
      status[7] = !status[7];
      digitalWrite(9, status[7]);
      break;

    case 0xFF5AA5:
      Serial.println("9");
      for (int i=0; i<8; i+=2) {
        status[i] = 1;
      }
      for (int i=1; i<8; i+=2) {
        status[i] = 0;
      }
      for (int i=2; i<10; i++) {
        digitalWrite(i, status[i-2]);
      }
      break;

    case 0xFF4AB5:
      Serial.println("0");
      for (int i=0; i<8; i+=2) {
        status[i] = 0;
      }
      for (int i=1; i<8; i+=2) {
        status[i] = 1;
      }
      for (int i=2; i<10; i++) {
        digitalWrite(i, status[i-2]);
      }
      break;

    case 0xFF42BD:
      Serial.println("*");
      for (int i=2; i<10; i++) {
        digitalWrite(i, HIGH);
        status[i-2] = 1;
      }
      break;

    case 0xFF52AD:
      Serial.println("#");
      for (int i=2; i<10; i++) {
        digitalWrite(i, LOW);
        status[i-2] = 0;
      }
      break;

    case 0xFF02FD:
      Serial.println("OK");
      for (int i=0; i<8; i++) {
        status[i] = !status[i];
      }
      for (int i=2; i<10; i++) {
        digitalWrite(i, status[i-2]);
      }
      break;

    case 0xFF22DD:
      Serial.println("LEFT");
      tmp_status = status[0];
      for (int i=0; i<7; i++) {
        status[i] = status[i+1];
      }
      status[7] = tmp_status;
      for (int i=2; i<10; i++) {
        digitalWrite(i, status[i-2]);
      }
      break;

    case 0xFF629D:
      Serial.println("UP");
      break;

    case 0xFFC23D:
      Serial.println("RIGHT");
      tmp_status = status[7];
      for (int i=7; i>0; i--) {
        status[i] = status[i-1];
      }
      status[0] = tmp_status;
      for (int i=2; i<10; i++) {
        digitalWrite(i, status[i-2]);
      }
      break;

    case 0xFFA857:
      Serial.println("DOWN");
      break;        
    }
    irrecv.resume(); // Receive the next value
  }
}
