#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Encoder.h>
#include <IRremote.h>  // Include the IRremote library for IR functionality

// Motor Pin Definitions for DC Worm Gear Motor (Conveyor)
extern const int IN1;    // Motor direction control for conveyor belt
extern const int IN2;
extern const int ENA;    // PWM speed control for conveyor belt motor

// Encoder Pins
extern const int encoderPinA; // Encoder A pin
extern const int encoderPinB; // Encoder B pin
extern Encoder conveyorEncoder;  // Encoder object to track motor pulses

// IR Receiver Pins and object
extern const int RECV_PIN;   // Define the digital pin for IR receiver
extern IRrecv irrecv;       // Create IR receiver object
extern decode_results results; // Store decoded IR signal

// Conveyor Control Flags
extern bool conveyorRunning;  // Track conveyor belt status (running or stopped)
extern long targetPulses;      // Target encoder pulses before stopping conveyor (adjust as needed)
extern long currentPulses;     // Track the current number of pulses

// Function Prototypes
void setupMotorControl();  // Initialize motors and servo
void moveTiltTo(long target);
void flipWrist(int angle);
void stopTilt();
void startConveyor();
void stopConveyor();
void processIR();          // Process IR signal to control conveyor belt

#endif
