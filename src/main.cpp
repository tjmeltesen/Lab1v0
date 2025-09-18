// ...existing code...
#include "server.h"
/*================================================================
+
+=  Simple WiFi Access Point + Web Server
+
+ Codes: 200 (OK), 404 (Not Found), 204 (No Content), 400 (Bad Request/Command Error) 
+
+===============================================================*/
const int GPIO_PIN19=19;
const int GPIO_PIN18=18;
struct Button {
  const uint8_t PIN;
  bool pressed;
};
Button button1 = {GPIO_PIN18, false};
Button button2 = {GPIO_PIN19, false};
void IRAM_ATTR button_pressed();
// ...existing code...
void setup() {
  Serial.begin(9600);
  server_setup();
  Serial.println("HTTP server started");
}

void loop() {
  // Server logic moved to server.cpp
  pinMode(button1.PIN, INPUT_PULLUP); //Will read a HIGH to Low transition
  pinMode(button2.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, button_pressed, FALLING);
  attachInterrupt(button2.PIN, button_pressed, FALLING);
  server_loop();
}



void IRAM_ATTR button_pressed() {
  // Handle button press interrupt
  // This is just a placeholder; actual implementation may vary
  // depending on how you want to handle button presses
  // For example, you might want to set a flag or increment a counter
  // Here, we'll just print to the Serial console for demonstration
  Serial.println("Button pressed!");
}