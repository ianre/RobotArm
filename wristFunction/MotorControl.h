#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Encoder.h>
#include <Servo.h>

// Motor Pin Definitions for DC motor (Tilt - Y-axis)
const int IN1 = 8;    // Motor direction control for tilt
const int IN2 = 9;
const int ENA = 10;   // PWM speed control for tilt

// Clamp Motor (Clamping DC motor for the spoon)
const int CLAMP_IN1 = 4;    // Motor direction control for clamp
const int CLAMP_IN2 = 5;
const int CLAMP_ENA = 6;    // PWM speed control for clamp

// Encoder Setup (for wrist tilt motor)
extern Encoder wristEnc;   // Connect encoder A/B wires from wrist motor to pins 2 and 3

// Microservo Pin (for wrist flip)
extern const int servoPin; // Pin for microservo (flip control)

// Motion Settings
extern long TILT_HORIZONTAL;     // Horizontal baseline position
extern long TILT_DIPPED;         // 60° below horizontal

extern long FLIP_ORIGINAL;       // Palm-up (positive Z-axis)
extern long FLIP_ROTATED180;     // Palm-down (negative Z-axis)

// Control parameters
extern const int PWM_SPEED;  // PWM value (0–255)
extern const int TOLERANCE;   // Allowed deviation from target

// Function Prototypes
void setupMotorControl();  // Call this function in setup() to initialize motors and servo
void moveTiltTo(long target);
void flipWrist(int angle);
void stopTilt();
void clampSpoon(bool clamp);
void stopClamp();

#endif
