#include <Arduino.h>

// put function declarations here:

#include <BluetoothSerial.h>

// Function to send a message over Bluetooth Serial
void sendBluetoothMessage(const String& message);
int myFunction(int, int);

void setup() {
  Serial.begin(9600); // Or use Serial1.begin(x115200, SERIAL_8N1, RX_PIN, TX_PIN);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }

  // Start Bluetooth Serial at default device name "ESP32test"
  static BluetoothSerial SerialBT;
  SerialBT.begin("ESP32test");
  sendBluetoothMessage("Hello");
}

// Function to send a message over Bluetooth Serial
void sendBluetoothMessage(const String& message) {
  static BluetoothSerial SerialBT;
  if (!SerialBT.hasClient()) {
    // Wait for a client to connect (optional, or just send anyway)
    // Serial.println("Waiting for Bluetooth client...");
  }
  SerialBT.println(message);
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
