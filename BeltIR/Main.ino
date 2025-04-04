#include "MotorControl.h"  // Include the motor control logic

void setup() {
  // Initialize the motors, IR receiver, and perform the wrist movements
  setupMotorControl();
}

void loop() {
  // Continuously process the IR signal to start or stop the conveyor belt
  processIR();

  // Monitor the encoder pulses to stop the conveyor after a set distance
  monitorConveyor();
}
