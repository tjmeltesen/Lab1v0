#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(9600); // Or use Serial1.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    Serial.print("Echo: ");
    Serial.println(received); // Send response back
  }
  delay(10);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}