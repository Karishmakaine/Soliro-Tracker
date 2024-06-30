#include <Energia.h>

// Motor pins (example pins, adjust based on your hardware setup)
const int motorLeftForwardPin = 5;
const int motorLeftBackwardPin = 6;
const int motorRightForwardPin = 9;
const int motorRightBackwardPin = 10;

// IR sensor pins (example pins, adjust based on your hardware setup)
const int irLeftPin = A0;
const int irRightPin = A1;

// IR sensor threshold (adjust based on sensor characteristics and environment)
const int irThreshold = 400;

void setup() {
  // Motor pins setup
  pinMode(motorLeftForwardPin, OUTPUT);
  pinMode(motorLeftBackwardPin, OUTPUT);
  pinMode(motorRightForwardPin, OUTPUT);
  pinMode(motorRightBackwardPin, OUTPUT);
  
  // IR sensor pins setup
  pinMode(irLeftPin, INPUT);
  pinMode(irRightPin, INPUT);
  
  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read IR sensor values
  int irLeftValue = analogRead(irLeftPin);
  int irRightValue = analogRead(irRightPin);
  
  // Determine obstacle presence based on IR sensor readings
  bool obstacleLeft = irLeftValue < irThreshold;
  bool obstacleRight = irRightValue < irThreshold;
  
  // Decision-making logic
  if (!obstacleLeft && !obstacleRight) {
    // No obstacle detected, move forward
    moveForward();
  } else if (!obstacleLeft && obstacleRight) {
    // Obstacle on the right, turn left
    turnLeft();
  } else if (obstacleLeft && !obstacleRight) {
    // Obstacle on the left, turn right
    turnRight();
  } else {
    // Obstacles on both sides, turn around or implement specific maze-solving logic
    turnAround();
  }
  
  // Print sensor values for debugging
  Serial.print("IR Left: ");
  Serial.print(irLeftValue);
  Serial.print(", IR Right: ");
  Serial.println(irRightValue);
  
  // Delay to control robot speed and processing
  delay(100);  // Adjust delay as needed
}

void moveForward() {
  digitalWrite(motorLeftForwardPin, HIGH);
  digitalWrite(motorLeftBackwardPin, LOW);
  digitalWrite(motorRightForwardPin, HIGH);
  digitalWrite(motorRightBackwardPin, LOW);
}

void turnLeft() {
  digitalWrite(motorLeftForwardPin, LOW);
  digitalWrite(motorLeftBackwardPin, HIGH);
  digitalWrite(motorRightForwardPin, HIGH);
  digitalWrite(motorRightBackwardPin, LOW);
  delay(500);  // Adjust turn duration based on robot speed and maze complexity
}

void turnRight() {
  digitalWrite(motorLeftForwardPin, HIGH);
  digitalWrite(motorLeftBackwardPin, LOW);
  digitalWrite(motorRightForwardPin, LOW);
  digitalWrite(motorRightBackwardPin, HIGH);
  delay(500);  // Adjust turn duration based on robot speed and maze complexity
}

void turnAround() {
  digitalWrite(motorLeftForwardPin, LOW);
  digitalWrite(motorLeftBackwardPin, HIGH);
  digitalWrite(motorRightForwardPin, LOW);
  digitalWrite(motorRightBackwardPin, HIGH);
  delay(1000);  // Adjust turn duration based on robot speed and maze complexity
}
