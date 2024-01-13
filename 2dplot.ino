#include <AccelStepper.h>
#include <Servo.h>

// Constants for stepper motor steps per revolution
const int STEPS_PER_REV_X = 200;
const int STEPS_PER_REV_Y = 200;

// Constants for pen servo motor
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 180;

// Pins for stepper motors
const int motorPinX1 = 2;  // Example, replace with your actual pin numbers
const int motorPinX2 = 3;
const int motorPinY1 = 4;
const int motorPinY2 = 5;

// Pins for servo motor
const int servoPin = 9;  // Example, replace with your actual pin number

AccelStepper stepperX(1, motorPinX1, motorPinX2);  // Stepper motor for X-axis
AccelStepper stepperY(1, motorPinY1, motorPinY2);  // Stepper motor for Y-axis
Servo penServo;  // Servo motor for pen movement

void setup() {
  Serial.begin(9600);
  penServo.attach(servoPin);
}

void moveStepper(AccelStepper &stepper, int steps, char axis) {
  Serial.print("Moving ");
  Serial.print(axis);
  Serial.print(" axis ");
  Serial.print(steps);
  Serial.println(" steps");
  
  stepper.setSpeed(500);  // Set a suitable speed
  stepper.moveTo(steps);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
}

void moveServo(int angle) {
  Serial.print("Moving servo to ");
  Serial.print(angle);
  Serial.println(" degrees");
  
  penServo.write(angle);
  delay(1000);  // Simulate the time it takes to move the servo motor
}

void plotPoint(int x, int y) {
  Serial.println("Plotting point");
  // You can add your own plotting logic here using external hardware or display
  delay(2000);  // Simulate the time it takes to plot
}

void printWords(String words) {
  int xSteps = STEPS_PER_REV_X / 2;
  int ySteps = STEPS_PER_REV_Y / 2;

  // Split the input string into words
  int startIdx = 0;
  int endIdx = words.indexOf(',');
  
  while (endIdx != -1) {
    String word = words.substring(startIdx, endIdx);
    
    moveServo(SERVO_MIN_ANGLE);  // Lift pen
    moveServo(SERVO_MAX_ANGLE);  // Lower pen
    moveStepper(stepperX, xSteps, 'X');  // Move carriage to starting position
    moveStepper(stepperY, ySteps, 'Y');  // Move carriage to starting position
    Serial.print("Printing: ");
    Serial.println(word);
    moveServo(SERVO_MIN_ANGLE);  // Lift pen
    plotPoint(0, 0);  // Simulate plotting at the origin

    delay(2000);  // Increased pause to 2 seconds to make it more visible
    
    startIdx = endIdx + 1;
    endIdx = words.indexOf(',', startIdx);
  }

  // Print the last word
  String lastWord = words.substring(startIdx);
  moveServo(SERVO_MIN_ANGLE);
  moveServo(SERVO_MAX_ANGLE);
  moveStepper(stepperX, xSteps, 'X');
  moveStepper(stepperY, ySteps, 'Y');
  Serial.print("Printing: ");
  Serial.println(lastWord);
  moveServo(SERVO_MIN_ANGLE);
  plotPoint(0, 0);
  delay(2000);
}

void loop() {
  // Example usage
  String inputWords = "Hello,World";  // Replace with your input
  printWords(inputWords);

  while (1);  // Stop the loop
}
