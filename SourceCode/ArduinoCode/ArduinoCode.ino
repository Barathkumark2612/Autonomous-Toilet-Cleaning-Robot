#include <SoftwareSerial.h>

SoftwareSerial nodemcu(3, 2); // RX, TX

//#define enA 10 //Enable1 L298 Pin enA
#define in1 4 //Motor1  L298 Pin in1 
#define in2 5 //Motor1  L298 Pin in1 
#define in3 6 //Motor2  L298 Pin in1 
#define in4 7 //Motor2  L298 Pin in1 
#define gas A0
#define pump 8
#define motor 9
//#define enB 10 //Enable2 L298 Pin enB

char data;
int gasValue;

void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  //  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
  pinMode(pump, OUTPUT);
  pinMode(motor, OUTPUT);
  //  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB
}

void loop() {
  forward();
  delay(5000);
  Stop();
  clean();
  backward();
  delay(2000);
  Stop();
  delay(1000);
  for (int i = 0; i < 10; i++) {
    gasValue = analogRead(gas);
    //  Serial.println(gasValue);
    if (gasValue >= 16) {
      Stop();
      clean();
    }
    if (nodemcu.available()) {
      while (1) {
        data = nodemcu.read();
        Serial.println(data);
        if (data == 'F') {
          forward();
        }

        if (data == 'B') {
          backward();
        }

        if (data == 'L') {
          turnLeft();
        }

        if (data == 'R') {
          turnRight();
        }

        if (data == 'S') {
          Stop();
        }
      }
    }
    delay(1000);
  }
}

void forward() { //forword
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void backward() { //backword
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void turnRight() { //turnRight
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void turnLeft() { //turnLeft
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void Stop() { //stop
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin
}

void clean() { //clean
  digitalWrite(pump, HIGH);
  delay(5000);
  digitalWrite(pump, LOW);
  delay(500);
  digitalWrite(motor, HIGH);
  delay(20000);
  digitalWrite(motor, LOW);
}
