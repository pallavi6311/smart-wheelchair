#define RAIN_SENSOR A0
#define BUZZER 8
#define TRIG 9
#define ECHO 10
#define SERVO 6

#include <Servo.h>
Servo canopy;

void setup() {
  pinMode(RAIN_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  canopy.attach(SERVO);
  canopy.write(0); // canopy closed
  Serial.begin(9600);
}

void loop() {
  // Rain detection
  int rainValue = analogRead(RAIN_SENSOR);
  if (rainValue < 400) { 
    Serial.println("🌧 Rain detected! Deploying canopy...");
    canopy.write(90); // deploy canopy
  } else {
    canopy.write(0); // close canopy
  }

  // Obstacle detection
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance < 30 && distance > 0) {
    Serial.println("⚠ Obstacle detected!");
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(500);
}
