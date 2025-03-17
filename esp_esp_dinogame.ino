// Install appropriate library on arduino ide
// use ESP 32 board 
// connection of circutry is 
// VCC-->3.3V
// GND-->GND
// SCL-->GPIO 22
// SDA-->GPIO 23
// PUSH BUTTON ONE LEG-->GPIO 18
//   ANOTHER LEG--->GND
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define JUMP_BUTTON 18  
#define DUCK_BUTTON 19  

int dinoY = 40;    
int cactusX = SCREEN_WIDTH;  
bool jumping = false;
bool ducking = false;
int jumpHeight = 20;  
int score = 0;

// Dino bitmap (10x10 pixels)
const uint8_t dino_bitmap[] = {
  0b00111000, 
  0b00101000, 
  0b00111000, 
  0b00001000, 
  0b00001000, 
  0b00001000, 
  0b00011100, 
  0b00010100, 
  0b00010100, 
  0b00000100  
};

// Cactus bitmap (8x15 pixels)
const uint8_t cactus_bitmap[] = {
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b01111110, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b00011000, 
  0b01111110  
};

void setup() {
    pinMode(JUMP_BUTTON, INPUT_PULLUP);
    pinMode(DUCK_BUTTON, INPUT_PULLUP);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  
        while (true);  // Halt if display init fails
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_BLACK);  // Draw text in "blue"
    display.setCursor(20, 30);
    display.print("ESP Dino Game!");
    delay(100);
    // display.display();
}

void loop() {
    if (digitalRead(JUMP_BUTTON) == LOW && !jumping && !ducking) {
        jumping = true;
    }

    if (digitalRead(DUCK_BUTTON) == LOW && !jumping) {
        ducking = true;
    } else {
        ducking = false;
    }

    if (jumping) {
        dinoY -= 3;
        if (dinoY <= 40 - jumpHeight) jumping = false;
    } else if (dinoY < 40) {
        dinoY += 3;
    }

    cactusX -= 3;
    if (cactusX < -10) {
        cactusX = SCREEN_WIDTH;
        score++;
    }

    // White background
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);

    // Draw dino
    if (ducking) {
        display.drawBitmap(10, 45, dino_bitmap, 8, 10, SSD1306_BLACK);
    } else {
        display.drawBitmap(10, dinoY, dino_bitmap, 8, 10, SSD1306_BLACK);
    }

    // Draw cactus
    display.drawBitmap(cactusX, 40, cactus_bitmap, 8, 15, SSD1306_BLACK);

    // Display score
    display.setCursor(90, 5);
    display.print("Score: ");
    display.print(score);

    // Collision detection
    if (cactusX < 20 && dinoY > 30 && !ducking) {
        display.setCursor(40, 30);
        display.print("Game Over!");
        display.display();
        delay(2000);
        cactusX = SCREEN_WIDTH;
        dinoY = 40;
        score = 0;
    }

    display.display();
    delay(50);
}
 
