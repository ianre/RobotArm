#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Encoder.h>

// Motor Pin Definitions
const int IN1 = 8;  // Motor direction control
const int IN2 = 9;
const int ENA = 10;  // PWM speed control

const int IN3 = 11;
const int IN4 = 12;
const int ENB = 6;

// Encoder Setup
Encoder tiltEnc(
    2, 3);  // Connect encoder A/B wires from tilt motor to pins 2 and 3
Encoder flipEnc(4, 5);  // Flip motor encoder connected to pins 4 and 5

// Motion Settings
long TILT_HORIZONTAL = 0;  // Horizontal baseline position
long TILT_DIPPED =
    -400;  // 60° below horizontal (negative if down increases counts)

long FLIP_ORIGINAL = 0;      // Original wrist orientation
long FLIP_ROTATED180 = 800;  // 180° rotation on X-axis

// Control parameters
const int PWM_SPEED = 150;  // PWM value (0–255)
const int TOLERANCE = 10;   // Allowed deviation from target

void moveTiltTo(long target);
void moveFlipTo(long target);
void stopTilt();
void stopFlip();

#endif
