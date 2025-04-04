#include "MotorControl.h"
#include <Arduino.h>  // Include Arduino library for PWM and digitalWrite

// Initialize the encoder for the wrist tilt motor
Encoder wristEnc(2, 3);  // Connect encoder A/B wires from wrist motor to pins 2 and 3

// Initialize the servo for wrist flipping
Servo wristFlipServo;  // Create a Servo object for the wrist flip

// Motion Settings
long TILT_HORIZONTAL = 0;     // Horizontal baseline position
long TILT_DIPPED = -400;      // 60° below horizontal (this value may need calibration)

long FLIP_ORIGINAL = 0;       // Palm-up (positive Z-axis)
long FLIP_ROTATED180 = 180;   // Palm-down (negative Z-axis)

// Control parameters
const int PWM_SPEED = 150;  // PWM value (0–255)
const int TOLERANCE = 10;   // Allowed deviation from target

void setup() {
  // Set all motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Set clamp motor control pins as outputs
  pinMode(CLAMP_IN1, OUTPUT);
  pinMode(CLAMP_IN2, OUTPUT);
  pinMode(CLAMP_ENA, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Reset encoder to 0 at startup
  wristEnc.write(0);

  // Attach the microservo to the pin
  wristFlipServo.attach(servoPin);

  // 1. Start Horizontal Palm-up
  moveTiltTo(TILT_HORIZONTAL);  // Move wrist to horizontal position (palm-up)
  delay(500);

  // 2. Clamp the spoon before dipping
  clampSpoon(true);  // Clamping the spoon before the wrist dips
  delay(500);

  // 3. Nod Downward Palm-up
  moveTiltTo(TILT_DIPPED);     // Move wrist 60° downward (palm-up)
  delay(500);

  // 4. Go Back to Horizontal Palm-up
  moveTiltTo(TILT_HORIZONTAL);  // Return wrist to horizontal position (palm-up)
  delay(500);

  // 5. Flip Wrist to Palm-down
  flipWrist(FLIP_ROTATED180);  // Flip wrist to palm-down (180°)
  delay(500);

  // 6. Unflip Wrist to Palm-up
  flipWrist(FLIP_ORIGINAL);    // Return wrist to palm-up (0°)
  delay(500);

  // 7. Unclamp the spoon after the movement is done
  clampSpoon(false);  // Unclamp the spoon after the wrist movement is complete
  delay(500);

  // 8. Return wrist to horizontal position (palm-up)
  moveTiltTo(TILT_HORIZONTAL);
  delay(500);
}

// Function to move the wrist tilt motor
void moveTiltTo(long target) {
  long pos = wristEnc.read();  // Read current position from encoder
  int speed = PWM_SPEED;       // Default speed

  while (abs(pos - target) > TOLERANCE) {
    // Adjust speed based on the error in position
    speed = map(abs(pos - target), 0, 400, 100, PWM_SPEED);  // Slow down as it gets closer to target

    if (pos < target) {
      digitalWrite(IN1, HIGH);  // Move forward (clockwise)
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN1, LOW);   // Move backward (counterclockwise)
      digitalWrite(IN2, HIGH);
    }

    analogWrite(ENA, speed);   // Set motor speed
    pos = wristEnc.read();     // Update position reading from the encoder
  }

  stopTilt();  // Stop motor after reaching target
}

// Function to flip wrist via microservo (rotate wrist 180° between palm-up and palm-down)
void flipWrist(int angle) {
  wristFlipServo.write(angle);  // Set the servo to the desired position
  Serial.print("Flipping wrist to: ");
  Serial.println(angle);
}

// Stops the tilt motor
void stopTilt() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// Function to control the clamp motor (clamp or unclamp)
void clampSpoon(bool clamp) {
  int speed = PWM_SPEED;

  if (clamp) {
    // Clamping (moving the motor in one direction)
    digitalWrite(CLAMP_IN1, HIGH);  // Clamp in one direction
    digitalWrite(CLAMP_IN2, LOW);
  } else {
    // Unclamping (moving the motor in the opposite direction)
    digitalWrite(CLAMP_IN1, LOW);   // Unclamp in the opposite direction
    digitalWrite(CLAMP_IN2, HIGH);
  }

  // Set clamp motor speed
  analogWrite(CLAMP_ENA, speed);

  // Run the motor for a set time to clamp or unclamp
  delay(2000);  // Adjust the time based on how long the clamp or unclamp action should take

  // Stop the clamp motor
  stopClamp();
}

// Function to stop the clamp motor
void stopClamp() {
  digitalWrite(CLAMP_IN1, LOW);
  digitalWrite(CLAMP_IN2, LOW);
  analogWrite(CLAMP_ENA, 0);
}
