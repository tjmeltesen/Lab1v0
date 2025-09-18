#include "server.h"
#include <WiFi.h>

int counter = 0;
bool RequestFlag = false;
const char* ssid = "ESP32TEST";
const char* password = "12345678";
const int GPIO_PIN19 = 19;
const int GPIO_PIN18 = 18;
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);

void server_setup() {
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);
    
    server.on("/", handle_OnConnect);

    server.on("/data", HTTP_POST, handle_request);

    server.on("/%", HTTP_POST, handle_BadCommand);
    server.onNotFound(handle_NotFound);
    
    server.begin();
	server.on("/", handle_OnConnect);
	server.on("/data", HTTP_POST, handle_request);
	server.on("/%", HTTP_POST, handle_BadCommand);
	server.onNotFound(handle_NotFound);
	server.begin();
	Serial.println("HTTP server started");
}

void server_loop() {
	server.handleClient();
	if (RequestFlag) {
		Serial.println("Data request received");
		for (int i = 0; i < 10; i++) {
			Serial.println("Data Item: " + String(i));
			delay(1000);
		}
		RequestFlag = false;
	}
}

void handle_OnConnect() {
	counter++;
	server.send(200, "text/html", createHTML());
}

void handle_request(){
	RequestFlag = true;
	server.send(200, "text/plain", "Sending Data");
}

void handle_NotFound() {
	server.send(404, "text/plain", "Not found");
}

void handle_BadCommand() {
	server.send(400, "text/plain", "Bad Request");
}

String createHTML() {
	String str = "<!DOCTYPE html><html>";
	str += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
	str += "<style>";
	str += "body {font-family: Arial, sans-serif; color: #444; text-align: center;}";
	str += ".title {font-size: 30px; font-weight: bold; letter-spacing: 2px; margin: 80px 0 55px;}";
	str += ".counter {font-size: 80px; font-weight: 300; line-height: 1; margin: 0px; color: #4285f4;}";
	str += ".button {font-size: 24px; padding: 20px 40px; margin-top: 40px; background: #4285f4; color: #fff; border: none; border-radius: 8px; cursor: pointer;}";
	str += "</style>";
	str += "<script>";
	str += "function sendData() { fetch('/data', {method: 'POST'}).then(r => r.text()).then(alert); }";
	str += "</script>";
	str += "</head>";
	str += "<body>";
	str += "<h1 class=\"title\">VISITOR COUNTER</h1>";
	str += "<button class=\"button\" onclick=\"sendData()\">Send Data</button>";
	str += "<div class=\"counter\"></div>";
	str += "</body></html>";
	return str;
}
