// Motor Driver Pin Definitions
const int IN1 = 8;   // Motor direction control pin 1
const int IN2 = 9;   // Motor direction control pin 2
const int ENA = 10;  // PWM speed control pin

// Control Parameters
const int PWM_SPEED = 255;   // Full speed (0–255)
const int CLAMP_TIME = 5000; // Time to clamp down in milliseconds (5 seconds)

void setup() {
  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Step 1: Clamp down on the spoon
  Serial.println("Clamping down on the spoon...");
  clampDown();

  // Wait for 5 seconds to simulate the clamping action
  delay(CLAMP_TIME);

  // Step 2: Unclamp (release the spoon)
  Serial.println("Releasing the spoon...");
  releaseSpoon();
}

void loop() {
  // The loop is empty since we don't want to repeat the action.
  // All actions occur in the setup() function.
}

// Function to clamp down on the spoon (move the motor in one direction)
void clampDown() {
  digitalWrite(IN1, HIGH);  // Set motor direction to clamp
  digitalWrite(IN2, LOW);   // Set motor direction to clamp
  analogWrite(ENA, PWM_SPEED); // Run motor at full speed
}

// Function to release the spoon (move the motor in the opposite direction)
void releaseSpoon() {
  digitalWrite(IN1, LOW);   // Set motor direction to release
  digitalWrite(IN2, HIGH);  // Set motor direction to release
  analogWrite(ENA, PWM_SPEED); // Run motor at full speed
}
