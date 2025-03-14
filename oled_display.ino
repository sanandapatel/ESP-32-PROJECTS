#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char* ssid = "SANANDA";
const char* password = "00111111";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WebServer server(80);

String displayText = " Sananda Patel   ";
int textPosition = SCREEN_WIDTH;

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>OLED Control</title></head><body>";
  html += "<h2>Enter text to display:</h2>";
  html += "<form action='/setText' method='POST'>";
  html += "<input type='text' name='text' placeholder='Enter text here' required>";
  html += "<button type='submit'>Update Display</button></form></body></html>";
  server.send(200, "text/html", html);
}

void handleSetText() {
  if (server.hasArg("text")) {
    displayText = " " + server.arg("text") + "   "; // Add spaces for smooth scrolling
    textPosition = SCREEN_WIDTH;
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setText", HTTP_POST, handleSetText);
  server.begin();
}

void loop() {
  server.handleClient();

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  int yPosition = (SCREEN_HEIGHT - 16) / 2; // Center text vertically

  // Display scrolling text
  display.setCursor(textPosition, yPosition);
  display.print(displayText);
  display.display();

  // Move text left
  textPosition--;

  // Reset text position when it moves fully out of view
  int textWidth = displayText.length() * 12; // Approx width of the text
  if (textPosition < -textWidth) {
    textPosition = SCREEN_WIDTH;
  }

  delay(50); // Adjust for smoother scrolling speed
}
