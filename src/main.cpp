#include <Arduino.h>

// put function declarations here:

#include <BluetoothSerial.h>

// Function to send a message over Bluetooth Serial
void sendBluetoothMessage(const String& message);
static BluetoothSerial SerialBT;
void setup() {
  Serial.begin(9600); // Or use Serial1.begin(x115200, SERIAL_8N1, RX_PIN, TX_PIN);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB
  }
  // Start Bluetooth Serial at default device name "ESP32test"
  SerialBT.begin("ESP32test");
}

// Function to send a message over Bluetooth Serial
void sendBluetoothMessage(const String& message) {
  static BluetoothSerial SerialBT;
  if (!SerialBT.hasClient()) {
    // Wait for a client to connect (optional, or just send anyway)
    Serial.println("Waiting for Bluetooth client...");
  }
  SerialBT.println(message);
}

void loop() {
  if (Serial.available()) {
    String received = Serial.readStringUntil('\n');
    Serial.println("Echo: "); // Send response back
    Serial.println(received); // Send response back
    SerialBT.println(received); // Forward to Bluetooth
  }
  if (SerialBT.available()) {
    String btReceived = SerialBT.readStringUntil('\n');
    Serial.print("Bluetooth Received: ");
    Serial.println(btReceived);
  }
  delay(20);
}

