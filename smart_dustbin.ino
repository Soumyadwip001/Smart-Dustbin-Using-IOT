#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define MOISTURE_PIN A0
#define SERVO_PIN 3

Servo lidServo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOISTURE_PIN, INPUT);
  
  lidServo.attach(SERVO_PIN);
  lidServo.write(0);  // Lid closed
  
  Serial.begin(9600);
}

void loop() {
  long duration, distance;

  // Read ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Read moisture sensor
  int moisture = analogRead(MOISTURE_PIN);
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Moisture: ");
  Serial.println(moisture);

  // If hand detected (less than 15 cm), open lid
  if (distance < 15) {
    lidServo.write(90);  // Open
    delay(3000);         // Keep open for 3 seconds
    lidServo.write(0);   // Close
  }

  delay(500);
}
