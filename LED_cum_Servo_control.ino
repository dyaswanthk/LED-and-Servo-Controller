#include <Servo.h>

const int LED_PIN = 11; 
const int SERVO_PIN = 9;
const int LED_INTERVAL = 1000;  // 1 second blinking interval

Servo myServo;
unsigned long previousMillis = 0;
bool ledState = LOW;
int currentAngle = 90;  // Starting position at 90 degrees

void setup() {
 
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  myServo.write(currentAngle);
}

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= LED_INTERVAL) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
  
  // Check for serial input to control servo
  if (Serial.available() > 0) {
    char command = Serial.read();
    
    switch(command) {
      case 'L':  // Left rotation (increase angle)
        currentAngle = min(180, currentAngle + 45);
        myServo.write(currentAngle);
        Serial.print("Moving Left. New angle: ");
        Serial.println(currentAngle);
        break;
      
      case 'R':  // Right rotation (decrease angle)
        currentAngle = max(0, currentAngle - 45);
        myServo.write(currentAngle);
        Serial.print("Moving Right. New angle: ");
        Serial.println(currentAngle);
        break;
      
      case 'C':  // Center position
        currentAngle = 90;
        myServo.write(currentAngle);
        Serial.println("Centering servo to 90 degrees");
        break;
        
      case '0' ... '9':  // Direct angle control in steps of 20 degrees
        int newAngle = (command - '0') * 20;
        currentAngle = min(180, newAngle);
        myServo.write(currentAngle);
        Serial.print("Setting angle to: ");
        Serial.println(currentAngle);
        break;
    }
  }
}