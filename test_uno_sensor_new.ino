#include <Servo.h>

Servo myservo1;
Servo myservo2;

unsigned long previousMillis = 0;
const long interval = 2000;                                             // 2 seconds interval
String dataToSend = "sensor1,sensor2,sensor3,sensor4,sensor5,sensor6";  // Comma-separated data

String sensor1;
String sensor2;
String sensor3;
String sensor4;
String sensor5;
String sensor6;


// Deklarasi pin sensor IR
int parking1_slot1_ir_s = 4;
int parking1_slot2_ir_s = 5;
int parking1_slot3_ir_s = 6;

int parking2_slot1_ir_s = 7;
int parking2_slot2_ir_s = 8;
int parking2_slot3_ir_s = 9;

int entrance_gate = 11;
int exit_gate = 12;

int pos1 = 90;  // entrance gate
int pos2 = 90;  // exit gate


void setup() {
  Serial.begin(115200);
  // ss.begin(115200);

  pinMode(parking1_slot1_ir_s, INPUT);
  pinMode(parking1_slot2_ir_s, INPUT);
  pinMode(parking1_slot3_ir_s, INPUT);

  pinMode(parking2_slot1_ir_s, INPUT);
  pinMode(parking2_slot2_ir_s, INPUT);
  pinMode(parking2_slot3_ir_s, INPUT);

  pinMode(entrance_gate, INPUT);
  pinMode(exit_gate, INPUT);

  myservo1.attach(13);
  myservo2.attach(3);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    p1slot1();
    p1slot2();
    p1slot3();
    p2slot1();
    p2slot2();
    p2slot3();

    gates();

    String dataToSend = sensor1 + "," + sensor2 + "," + sensor3 + "," + sensor4 + "," + sensor5 + "," + sensor6 + ",";

    Serial.println(dataToSend); // Send data to ESP8266
    //Serial.print("Sent data to ESP8266: ");
    Serial.println(dataToSend);

    digitalWrite(parking1_slot1_ir_s, HIGH);
    digitalWrite(parking1_slot2_ir_s, HIGH);
    digitalWrite(parking1_slot3_ir_s, HIGH);
    digitalWrite(parking2_slot1_ir_s, HIGH);
    digitalWrite(parking2_slot2_ir_s, HIGH);
    digitalWrite(parking2_slot3_ir_s, HIGH);
    digitalWrite(entrance_gate, HIGH);
    digitalWrite(exit_gate, HIGH);

    delay(1000);
  }
}

void p1slot1()  // parkng 1 slot1
{
  if (digitalRead(parking1_slot1_ir_s) == LOW) {
    sensor1 = "1";
  } else {
    sensor1 ="0";
  }
}

void p1slot2()  // parking 1 slot2
{
  if (digitalRead(parking1_slot2_ir_s) == LOW) {
    sensor2 = "1";
  } else {
    sensor2 = "0";
  }
}

void p1slot3()  // parking 1 slot3
{
  if (digitalRead(parking1_slot3_ir_s) == LOW) {
    sensor3 = "1";
  } else {
    sensor3 = "0";
  }
}

// Parkir 2

void p2slot1()  // parking 2 slot1
{
  if (digitalRead(parking2_slot1_ir_s) == LOW) {
    sensor4 = "1";
  } else { 
    sensor4 = "0";
  }
}

void p2slot2()  // parking 2 slot2
{
  if (digitalRead(parking2_slot2_ir_s) == LOW) {
    sensor5 = "1";
  } else {
    sensor5 = "0";
  }
}

void p2slot3()  // parking 2 slot3
{
  if (digitalRead(parking2_slot3_ir_s) == LOW) {
    sensor6 = "1";
  } else {
    sensor6 = "0";
  } 
}


// for the gates

void gates() {
  if (digitalRead(exit_gate) == LOW) {
    for (pos2 = 90; pos2 <= 180; pos2 += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo2.write(pos2);  // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position
    }
    delay(1000);
    for (pos2 = 180; pos2 >= 90; pos2 -= 1) {  // goes from 180 degrees to 0 degrees
      myservo2.write(pos2);                    // tell servo to go to position in variable 'pos'
      delay(15);                               // waits 15ms for the servo to reach the position
    }
  }

  if (((digitalRead(entrance_gate) == LOW)) && ((digitalRead(parking1_slot1_ir_s) == HIGH) || (digitalRead(parking1_slot2_ir_s) == HIGH) || (digitalRead(parking1_slot3_ir_s) == HIGH) || (digitalRead(parking2_slot1_ir_s) == HIGH) || (digitalRead(parking2_slot2_ir_s) == HIGH) || (digitalRead(parking2_slot3_ir_s) == HIGH))) {
    for (pos1 = 90; pos1 <= 180; pos1 += 1) {  // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo1.write(pos1);  // tell servo to go to position in variable 'pos'
      delay(15);             // waits 15ms for the servo to reach the position
    }
    delay(1000);
    for (pos1 = 180; pos1 >= 90; pos1 -= 1) {  // goes from 180 degrees to 0 degrees
      myservo1.write(pos1);                    // tell servo to go to position in variable 'pos'
      delay(15);                               // waits 15ms for the servo to reach the position
    }
  }
}