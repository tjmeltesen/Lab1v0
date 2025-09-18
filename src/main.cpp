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

// ...existing code...
void setup() {
  Serial.begin(9600);
  server_setup();
  Serial.println("HTTP server started");
}

void loop() {
  // Server logic moved to server.cpp
  server_loop();
}

