#include "TinyIRSender.hpp"

void setup() {
  sendNEC(3, 0, 11, 200); // Send address 0 and command 11 on pin 3 with 2 repeats.
}

void loop() {}