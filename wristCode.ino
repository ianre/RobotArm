// uses Encoder, assumes pin locations, PWD, and both motors are DC motors with L298 drivers, both motors have all ranges of motion, motors driven with PWM signals, motor directions controlled with direction pins

#include <Encoder.h>  // Include the Encoder library for quadrature encoder handling

// -------------------------
// Motor Pin Definitions
// -------------------------

// Tilt Motor (Y-axis)
const int IN1 = 8;    // Motor direction control
const int IN2 = 9;
const int ENA = 10;   // PWM speed control

// Flip Motor (X-axis)
const int IN3 = 11;
const int IN4 = 12;
const int ENB = 6;

// -------------------------
// Encoder Setup
// -------------------------

// Create Encoder objects for tilt and flip
Encoder tiltEnc(2, 3);   // Connect encoder A/B wires from tilt motor to pins 2 and 3
Encoder flipEnc(4, 5);   // Flip motor encoder connected to pins 4 and 5

// -------------------------
// Motion Settings
// -------------------------

// Encoder target positions (you will calibrate these based on your setup)
long TILT_HORIZONTAL = 0;     // Horizontal baseline position
long TILT_DIPPED     = -400;  // 60° below horizontal (negative if down increases counts)

long FLIP_ORIGINAL    = 0;    // Original wrist orientation
long FLIP_ROTATED180  = 800;  // 180° rotation on X-axis

// Control parameters
const int PWM_SPEED = 150;  // PWM value (0–255)
const int TOLERANCE = 10;   // Allowed deviation from target

// -------------------------
// Setup
// -------------------------

void setup() {
  // Set all motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Initialize serial communication for debugging or calibration
  Serial.begin(9600);

  // Reset encoders to 0 at startup (optional but helpful)
  tiltEnc.write(0);
  flipEnc.write(0);
}

// -------------------------
// Main Sequence Loop
// -------------------------

void loop() {
  // 1. Move to horizontal position
  moveTiltTo(TILT_HORIZONTAL);
  delay(500);

  // 2. Dip 60° downward
  moveTiltTo(TILT_DIPPED);
  delay(500);

  // 3. Return to horizontal
  moveTiltTo(TILT_HORIZONTAL);
  delay(500);

  // 4. Flip wrist 180° on X-axis
  moveFlipTo(FLIP_ROTATED180);
  delay(500);

  // 5. Return (unflip) to original orientation
  moveFlipTo(FLIP_ORIGINAL);
  delay(500);

  // Stop further looping
  while (true);
}

// -------------------------
// Movement Functions
// -------------------------

// Move tilt motor with dynamic speed adjustment
void moveTiltTo(long target) {
  long pos = tiltEnc.read();  // Read current position
  int speed = PWM_SPEED;      // Default speed

  while (abs(pos - target) > TOLERANCE) {
    // Adjust speed based on the error in position
    speed = map(abs(pos - target), 0, 400, 100, PWM_SPEED);  // Slow down as it gets closer to target

    if (pos < target) {
      digitalWrite(IN1, HIGH);  // Move forward
      digitalWrite(IN2, LOW);
    } else {
      digitalWrite(IN1, LOW);   // Move backward
      digitalWrite(IN2, HIGH);
    }

    analogWrite(ENA, speed);   // Set motor speed
    pos = tiltEnc.read();      // Update position reading
  }

  stopTilt();  // Stop motor after reaching target
}

// Moves flip motor to the target encoder value
void moveFlipTo(long target) {
  long pos = flipEnc.read();  // Read current flip position

  while (abs(pos - target) > TOLERANCE) {
    if (pos < target) {
      digitalWrite(IN3, HIGH);  // Move forward
      digitalWrite(IN4, LOW);
    } else {
      digitalWrite(IN3, LOW);   // Move backward
      digitalWrite(IN4, HIGH);
    }

    analogWrite(ENB, PWM_SPEED);  // Set motor speed
    pos = flipEnc.read();         // Update position reading
  }

  stopFlip();  // Stop motor after reaching target
}

// Stops the tilt motor
void stopTilt() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// Stops the flip motor
void stopFlip() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
