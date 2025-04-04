#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Encoder.h>
#include <Servo.h>

// Motor Pin Definitions for DC motor (Tilt - Y-axis)
const int IN1 = 8;    // Motor direction control
const int IN2 = 9;
const int ENA = 10;   // PWM speed control

// Encoder Setup for wrist tilt motor
extern Encoder wristEnc;   // Connect encoder A/B wires from wrist motor to pins 2 and 3

// Servo Pin for wrist flip
extern const int servoPin; // Pin for microservo (flip control)

// Motion Settings
extern long TILT_HORIZONTAL;     // Horizontal baseline position
extern long TILT_DIPPED;         // 60° below horizontal

extern long FLIP_ORIGINAL;       // Palm-up (positive Z-axis)
extern long FLIP_ROTATED180;     // Palm-down (negative Z-axis)

// Control parameters
extern const int PWM_SPEED;  // PWM value (0–255)
extern const int TOLERANCE;   // Allowed deviation from target

void moveTiltTo(long target);
void flipWrist(int angle);
void stopTilt();

#endif
