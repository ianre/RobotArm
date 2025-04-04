#include "MotorControl.h"  // Include the motor control logic

// Setup
void setup() {
  // Set all motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Attach the microservo to the pin
  wristFlipServo.attach(servoPin);

  // Reset encoder to 0 at startup
  wristEnc.write(0);

  // 1. Start Horizontal Palm-up
  moveTiltTo(TILT_HORIZONTAL);  // Move wrist to horizontal position (palm-up)
  delay(500);

  // 2. Nod Downward Palm-up
  moveTiltTo(TILT_DIPPED);     // Move wrist 60° downward (palm-up)
  delay(500);

  // 3. Go Back to Horizontal Palm-up
  moveTiltTo(TILT_HORIZONTAL);  // Return wrist to horizontal position (palm-up)
  delay(500);

  // 4. Flip Wrist to Palm-down
  flipWrist(FLIP_ROTATED180);  // Flip wrist to palm-down (180°)
  delay(500);

  // 5. Unflip Wrist to Palm-up
  flipWrist(FLIP_ORIGINAL);    // Return wrist to palm-up (0°)
  delay(500);

  // 6. Return wrist to horizontal position (palm-up)
  moveTiltTo(TILT_HORIZONTAL);
  delay(500);
}

// Loop function (empty)
void loop() {
  // The loop is empty since we only want to execute the actions once in setup().
}
