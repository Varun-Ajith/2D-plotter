#include <AccelStepper.h>
#include <Servo.h>

// Constants for stepper motor steps per revolution
const int STEPS_PER_REV_X = 200;
const int STEPS_PER_REV_Y = 200;

// Constants for pen servo motor
const int SERVO_MIN_ANGLE = 0;
const int SERVO_MAX_ANGLE = 180;

// Pins for stepper motors
const int motorPinX1 = 2;  
const int motorPinX2 = 3;
const int motorPinY1 = 4;
const int motorPinY2 = 5;

// Pins for servo motor
const int servoPin = 9;  

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
  
  stepper.setSpeed(500);  
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
  delay(1000);  
}

void plotPoint(int x, int y) {
  Serial.println("Plotting point");

  // plotter control logic
  int penUpPosition = 90;  //angle to lift the pen
  int penDownPosition = 180;  // angle to lower the pen

  // Move the pen up
  moveServo(penUpPosition);

  moveStepper(stepperX, x * STEPS_PER_REV_X / 100, 'X');
  moveStepper(stepperY, y * STEPS_PER_REV_Y / 100, 'Y');

  moveServo(penDownPosition);

  delay(2000);

  moveServo(penUpPosition);
}

void printWords(String words) {
  int xSteps = STEPS_PER_REV_X / 2;
  int ySteps = STEPS_PER_REV_Y / 2;

  int startIdx = 0;
  int endIdx = words.indexOf(',');
  
  while (endIdx != -1) {
    String word = words.substring(startIdx, endIdx);
    
    moveServo(SERVO_MIN_ANGLE);  // Lift pen
    moveServo(SERVO_MAX_ANGLE);  // Lower pen
    moveStepper(stepperX, xSteps, 'X');  // Move to starting position
    moveStepper(stepperY, ySteps, 'Y');  // Move to starting position
    Serial.print("Printing: ");
    Serial.println(word);
    moveServo(SERVO_MIN_ANGLE);  // Lift pen
    plotPoint(0, 0);  // Simulate plotting at the origin

    delay(2000);  // Made delay to 2 seconds to make it more visible in simulation
    
    startIdx = endIdx + 1;
    endIdx = words.indexOf(',', startIdx);
  }

  //last word
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
  String inputWords = "2-Dimensional Plotter";  
  printWords(inputWords);

  while (1);  
}
