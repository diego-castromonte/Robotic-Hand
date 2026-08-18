#include <Stepper.h>
#include <Servo.h>

Servo pinky, ring, middle, index, thumb, palm;

// Hand pins 
const int PinkyPin = 7;
const int RingPin = 6;
const int MiddlePin = 5;
const int IndexPin = 4;
const int ThumbPin = 3;
const int PalmPin = 2;

// Rotation Base
const int potPin = A0; 
const int StepsPerRevolution = 2048;
const int rpm = 10;
Stepper myStepper(StepsPerRevolution, 8, 10, 9, 11);
int previousVal = 0; 

// Servo Palm
const int PalmPotPin = A1; 
int previousPalmVal = -1;

// Fingers Potentiometer 
const int HandPotPin = A2;
int previousHandVal = -1;

void resetAll() {
  pinky.write(180);
  ring.write(180);
  middle.write(180);
  index.write(180);
  palm.write(180);
  thumb.write(180);
  Serial.println("All reset");
}

void setup() {
  Serial.begin(115200);
  myStepper.setSpeed(rpm);

  pinky.attach(PinkyPin);
  ring.attach(RingPin);
  middle.attach(MiddlePin);
  index.attach(IndexPin);
  palm.attach(PalmPin);
  thumb.attach(ThumbPin);

  resetAll();
  
  // Initialize baseline analog readings
  previousVal = analogRead(potPin);
  previousPalmVal = map(analogRead(PalmPotPin), 0, 1023, 0, 180);
  previousHandVal = map(analogRead(HandPotPin), 0, 1023, 0, 180);
}

void loop() {
  // 1. Base Stepper Rotation (Incremental movement)
  int currentVal = analogRead(potPin);
  int diff = currentVal - previousVal;
  if (abs(diff) > 5) { // Small noise deadband
    myStepper.step(diff > 0 ? 2 : -2); // Incremental steps to prevent blocking
    previousVal += (diff > 0 ? 2 : -2);
  }

  // 2. Palm Servo (Only updates if knob is actively turned)
  int palmRaw = analogRead(PalmPotPin);
  int currentPalmVal = map(palmRaw, 0, 1023, 0, 180);
  if (abs(currentPalmVal - previousPalmVal) > 2) {
    palm.write(currentPalmVal);
    previousPalmVal = currentPalmVal;
  }

  // 3. Serial Keyboard Commands
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if      (cmd == "1o") { pinky.write(0); }
    else if (cmd == "1c") { pinky.write(180); }
    else if (cmd == "2o") { ring.write(0); }
    else if (cmd == "2c") { ring.write(180); }
    else if (cmd == "3c") { middle.write(180); }
    else if (cmd == "3o") { middle.write(0); }
    else if (cmd == "4c") { index.write(180); }
    else if (cmd == "4o") { index.write(0); }
    else if (cmd == "5o") { thumb.write(180); }
    else if (cmd == "5c") { thumb.write(0); }
    else if (cmd == "R" || cmd == "r") { resetAll(); }
    else { Serial.println("Invalid Command"); }
  }

  // 4. Hand Potentiometer (Only overrides servos if knob is actively rotated)
  int handRaw = analogRead(HandPotPin);
  int currentHandVal = map(handRaw, 0, 1023, 0, 180);
  if (abs(currentHandVal - previousHandVal) > 2) {
    pinky.write(currentHandVal);
    ring.write(currentHandVal);
    middle.write(currentHandVal);
    index.write(currentHandVal);
    thumb.write(180 - currentHandVal);
    previousHandVal = currentHandVal;
  }

  delay(5);
}