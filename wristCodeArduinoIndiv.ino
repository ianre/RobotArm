#include <Encoder.h>  // Include the Encoder library for quadrature encoder handling
#include <Servo.h>    // Include the Servo library for controlling the microservo

// -------------------------
// Motor Pin Definitions
// -------------------------

// DC Motor (Tilt - Y-axis)
const int IN1 = 8;    // Motor direction control
const int IN2 = 9;
const int ENA = 10;   // PWM speed control

// Encoder Setup (for wrist tilt motor)
Encoder wristEnc(2, 3);   // Connect encoder A/B wires from wrist motor to pins 2 and 3

// Microservo Pin (for wrist flip)
const int servoPin = 11; // Pin for microservo (flip control)

// -------------------------
// Motion Settings
// -------------------------

long TILT_HORIZONTAL = 0;     // Horizontal baseline position (starting point)
long TILT_DIPPED     = -400;  // 60° below horizontal (this value may need calibration)

long FLIP_ORIGINAL   = 0;     // Palm-up (positive Z-axis)
long FLIP_ROTATED180 = 180;   // Palm-down (negative Z-axis)

// Control parameters
const int PWM_SPEED = 150;  // PWM value (0–255)
const int TOLERANCE = 10;   // Allowed deviation from target

// -------------------------
// Setup
// -------------------------

Servo wristFlipServo;  // Create a Servo object for the wrist flip

void setup() {
  // Set all motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Reset encoder to 0 at startup
  wristEnc.write(0);

  // Attach the microservo to the pin
  wristFlipServo.attach(servoPin);

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
}

// -------------------------
// Main Sequence Loop
// -------------------------
void loop() {
  // The loop is empty since we only want to execute the actions once in setup().
}

// -------------------------
// Movement Functions
// -------------------------

// Move tilt motor with dynamic speed adjustment
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

// Function to control wrist flip via microservo (rotate wrist 180° between palm-up and palm-down)
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
