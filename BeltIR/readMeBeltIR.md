# Conveyor Belt with DC Worm Gear Motor and IR Control

## Overview:
This system controls a **conveyor belt** using a **DC worm gear motor** with **encoder feedback**. The **IR receiver** receives signals from an IR remote to **start** and **stop** the conveyor belt.

## Key Features:
1. **IR Control**: The conveyor belt is controlled by pressing buttons on an **IR remote**.
   - **Start Conveyor**: When the correct IR signal is received, the conveyor starts.
   - **Stop Conveyor**: When another IR signal is received, the conveyor stops.
   
2. **Encoder Feedback**: The encoder counts pulses as the motor rotates. The conveyor belt will stop after a set number of rotations/pulses to ensure precise movement.
   
3. **Conveyor Belt Monitoring**: The system uses encoder pulses to detect when the conveyor has moved a certain distance and stops the motor automatically.

## Hardware Required:
1. **DC Worm Gear Motor**: Used to control the conveyor belt's motion.
2. **Encoder**: Tracks the rotations of the motor.
3. **IR Receiver**: Receives signals from the IR remote control.
4. **IR Remote**: Sends signals to start/stop the conveyor belt.
5. **Motor Driver (H-Bridge)**: Controls the motor's direction and speed.
6. **Arduino Board** (e.g., Arduino Uno): Used to process the signals and control the motor.

## Wiring:
1. **DC Motor**: Connect the motor to the H-Bridge motor driver (e.g., **L298N**).
2. **IR Receiver**: Connect the IR receiver to **pin 2** of the Arduino board.
3. **Encoder**: Connect the encoder's A and B pins to **pins 2 and 3** of the Arduino.
4. **Motor Driver (L298N)**:
   - IN1, IN2 pins to **pins 8 and 9** of the Arduino.
   - ENA pin to **pin 10** for PWM control.

## Code Flow:
1. **Initialization**: 
   - The motor and IR receiver are initialized at the start.
   - The motor is initially stopped.
   
2. **IR Signal Handling**:
   - The program listens for IR signals.
   - **Start signal**: Starts the conveyor belt.
   - **Stop signal**: Stops the conveyor belt.

3. **Pulse Monitoring**:
   - The encoder tracks how many pulses the motor has generated.
   - After reaching a set pulse count (based on desired movement distance), the conveyor stops.

## Calibration:
- Adjust the **`targetPulses`** value based on the specific gear ratio of the worm gear motor and the length of your conveyor belt.
- **Test with different values** of `targetPulses` to match the distance the conveyor should move before stopping.

## Key Assumptions:
1. **DC Worm Gear Motor** is used for the conveyor belt, providing high torque and self-locking behavior.
2. **IR Remote** sends specific signals to start or stop the conveyor belt (codes `0xF00FF` and `0xF0FF00` are placeholders and should be adjusted).
3. The system automatically stops the conveyor after a **set number of rotations** (adjusted with `targetPulses`).
4. The **encoder** tracks motor pulses to ensure precise control over the belt's movement.
5. The system assumes that the conveyor belt and robot arm are mounted securely to prevent falling off during operation.

---

### **Summary**:
This setup provides a complete system for controlling a **conveyor belt** with an IR remote, where the belt automatically stops after moving a set distance based on **encoder feedback**. The system allows precise control over the belt's motion while keeping the robot arm stable and secure on the conveyor.
