#include "MotorControl.h"
#include <Arduino.h>  // Include Arduino library for PWM and digitalWrite
#include <Encoder.h>
#include <IRremote.h>

// Motor Pin Definitions for DC Worm Gear Motor (Conveyor)
const int IN1 = 8;    // Motor direction control for conveyor belt
const int IN2 = 9;
const int ENA = 10;   // PWM speed control for conveyor belt motor

// Encoder Setup for DC Worm Gear Motor
const int encoderPinA = 2; // Encoder A pin
const int encoderPinB = 3; // Encoder B pin
Encoder conveyorEncoder(encoderPinA, encoderPinB); // Encoder object to track motor pulses

// IR Receiver Pins
const int RECV_PIN = 2;  // Define the digital pin for IR receiver
IRrecv irrecv(RECV_PIN); // Create IR receiver object
decode_results results;  // Store decoded IR signal

// Conveyor Control Flags
bool conveyorRunning = false;  // Track conveyor belt status (running or stopped)
long targetPulses = 1000;      // Target encoder pulses before stopping conveyor (adjust as needed)
long currentPulses = 0;        // Track the current number of pulses

// Setup the motor, IR receiver, and initialize conveyor to stopped
void setupMotorControl() {
  Serial.begin(9600);  // Start serial communication
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("IR Receiver Ready!");

  // Set motor control pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Initialize the conveyor belt to stop initially
  stopConveyor();
}

// Start the conveyor belt
void startConveyor() {
  digitalWrite(IN1, HIGH);  // Set the direction to forward
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);    // Set motor speed to max (255)
  conveyorRunning = true;   // Set conveyor running flag to true
}

// Stop the conveyor belt
void stopConveyor() {
  digitalWrite(IN1, LOW);   // Stop the motor by turning off both directions
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);      // Turn off PWM (no speed)
  conveyorRunning = false;  // Set conveyor running flag to false
}

// Process the IR signal to control the conveyor belt
void processIR() {
  if (irrecv.decode(&results)) { // If an IR signal is received
    Serial.print("Received IR Code: ");
    Serial.println(results.value, HEX); // Print in HEX format

    if (results.value == 0xF00FF) { // IR signal to start conveyor
      if (!conveyorRunning) {
        startConveyor();
        Serial.println("Conveyor Started");
      } else {
        Serial.println("Conveyor is already running.");
      }
    }
    else if (results.value == 0xF0FF00) { // IR signal to stop conveyor
      if (conveyorRunning) {
        stopConveyor();
        Serial.println("Conveyor Stopped");
      } else {
        Serial.println("Conveyor is already stopped.");
      }
    }

    irrecv.resume(); // Receive the next IR value
  }
}

// Monitor the number of pulses from the encoder to stop the conveyor
void monitorConveyor() {
  currentPulses = conveyorEncoder.read(); // Get current encoder pulse count
  if (currentPulses >= targetPulses) {
    // Stop the conveyor after reaching the target number of pulses
    stopConveyor();
    Serial.println("Conveyor Stopped after reaching target pulses");
  }
}
