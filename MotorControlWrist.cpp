#include "MotorControl.h"

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

// Function to stop the wrist tilt motor
void stopTilt() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}
