// Key Assumptions:
// 1. The DC motors control the wrist tilt (Y-axis) and clamp using PWM for speed and direction control.
// 2. The tilt motor uses an encoder for position feedback to ensure precise wrist tilt control (up and down).
// 3. The clamp motor is a DC motor controlled by PWM speed and direction pins (using CLAMP_IN1, CLAMP_IN2, and CLAMP_ENA).
// 4. The microservo controls wrist flipping (palm-up to palm-down) with rotation between 0° and 180°.
// 5. The encoder is connected to pins 2 and 3, and the microservo is connected to pin 11.
// 6. The wrist tilt motor moves from a horizontal palm-up position to 60° downward** and returns to the horizontal position.
// 7. The wrist flip** uses a servo to rotate the wrist from **palm-up (0°) to palm-down (180°).
// 8. The **clamp** will engage before dipping and disengage after the movement (clamp using `clampSpoon(true)` and unclamp using `clampSpoon(false)`).
// 9. The **clamp motor** will run for a set time of 2 seconds during clamping and unclamping (adjustable using `delay(2000)`).
// 10. **Arduino IDE** is used for compiling and uploading this code to the Arduino board.
// 11. The **motor drivers** (e.g., L298N or L293D) are assumed to be properly connected for the DC motors.
// 12. The **DC motors** and **servo** are powered appropriately (either via USB or external power supply).
// 13. The **encoder readings** and **servo angles** (e.g., for 0° and 180°) may need calibration depending on the specific setup.
// 14. The **wrist tilt** position is assumed to be controlled by **encoder feedback**, while the **clamp motor** runs for a fixed time duration.
// 15. The **pins** for motor control and servo are correctly connected to the corresponding **Arduino pins**.

#include <Encoder.h>  // Include the Encoder library for quadrature encoder handling
#include <Servo.h>    // Include the Servo library for controlling the microservo

// -------------------------
// Motor Pin Definitions
// -------------------------

// DC Motor (Tilt - Y-axis)
const int IN1 = 8;    // Motor direction control for tilt
const int IN2 = 9;
const int ENA = 10;   // PWM speed control for tilt

// Clamp Motor (Clamping DC motor for the spoon)
const int CLAMP_IN1 = 4;    // Motor direction control for clamp
const int CLAMP_IN2 = 5;
const int CLAMP_ENA = 6;    // PWM speed control for clamp

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

// -------------------------
// Clamp Motor Control
// -------------------------

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
