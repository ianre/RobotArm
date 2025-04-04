# Key Assumptions for Wrist and Clamp Control System

### Hardware Assumptions:
1. **DC Motors**: 
   - Used for controlling the wrist tilt (Y-axis) and clamp action (DC motor for clamping the spoon).
   - DC motors require motor driver circuits such as L298N or L293D to handle the direction and speed control.

2. **Encoder**: 
   - The wrist tilt motor uses an encoder connected to pins 2 and 3 for position feedback.
   - Encoder feedback ensures that the wrist motor moves to the exact target position.

3. **Microservo**: 
   - Used to rotate the wrist for **flipping** from **palm-up** (0°) to **palm-down** (180°).
   - The servo is connected to pin 11 and is controlled using the Servo library.

4. **Motor Pin Connections**: 
   - **DC motors for wrist tilt** are controlled by pins `IN1`, `IN2`, and `ENA`.
   - **DC motor for clamping** is controlled by pins `CLAMP_IN1`, `CLAMP_IN2`, and `CLAMP_ENA`.
   - **Microservo** is controlled by pin `servoPin = 11`.

### Functionality Assumptions:
5. **Wrist Tilt**:
   - The wrist tilts using the **DC motor** with encoder feedback, which ensures precise control of wrist positioning (horizontal or 60° downward).
   - The `moveTiltTo()` function moves the wrist to a target position based on encoder feedback.

6. **Wrist Flip**:
   - The **microservo** controls wrist rotation between **palm-up** and **palm-down**.
   - The `flipWrist()` function sets the wrist flip angle to either **0° (palm-up)** or **180° (palm-down)**.

7. **Clamp Operation**:
   - The **clamp motor** is controlled to **clamp** and **unclamp** the spoon using the `clampSpoon(true)` for clamping and `clampSpoon(false)` for unclamping.
   - The clamp motor runs for **2 seconds** during each action (clamping/unclamping), which can be adjusted based on physical setup.

### Timing Assumptions:
8. **Delays**: 
   - The `delay(500)` after each movement action provides sufficient time for mechanical movement.
   - The clamp motor runs for **2 seconds** during each clamping and unclamping action, controlled by `delay(2000)`.

### Arduino IDE Assumptions:
9. **Arduino IDE**:
   - The code is written for the Arduino IDE and can be directly uploaded to an Arduino board.
   - The **`Servo`** and **`Encoder`** libraries must be installed in the Arduino IDE.

### Calibration and Tuning Assumptions:
10. **Motor and Encoder Calibration**:
    - The `TILT_DIPPED` value should be calibrated for the specific motor and encoder setup to achieve a 60° downward movement.
    - The **servo angles** (0° and 180°) should be calibrated to match the wrist's range of motion from **palm-up** to **palm-down**.

11. **Power Supply**:
    - The **Arduino** board is powered either via USB or an external power source.
    - The **DC motors** and **servo** are powered by an external power supply that meets the voltage and current requirements of the motors and servo.

### Additional Notes:
12. This system assumes that proper **motor driver circuits** are in place to handle the current and voltage for the DC motors and that the servo is correctly powered and controlled.
13. You may need to adjust the timing (`delay()`) values based on the actual physical characteristics of the motors and servo.
