#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

// Motor driver 1 pins
#define IN11 13
#define IN12 12
#define IN13 14
#define IN14 27

// Motor driver 2 pins
#define IN21 26
#define IN22 25
#define IN23 33
#define IN24 32

void setup() {
  // Set all motor pins as OUTPUT
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  pinMode(IN13, OUTPUT);
  pinMode(IN14, OUTPUT);  

  pinMode(IN21, OUTPUT); 
  pinMode(IN22, OUTPUT);
  pinMode(IN23, OUTPUT);
  pinMode(IN24, OUTPUT);

  // Start Bluetooth Serial
  SerialBT.begin("ESP32_RC_BOT"); // Bluetooth name
  Serial.begin(115200);
  Serial.println("Bluetooth RC Bot Ready");
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println(command);

    switch (command) {
      case 'F': // Forward
        digitalWrite(IN11, HIGH);
        digitalWrite(IN12, LOW);
        digitalWrite(IN13, HIGH);
        digitalWrite(IN14, LOW);

        digitalWrite(IN21, HIGH);
        digitalWrite(IN22, LOW);
        digitalWrite(IN23, HIGH);
        digitalWrite(IN24, LOW);
        break;

      case 'B': // Backward
        digitalWrite(IN11, LOW);
        digitalWrite(IN12, HIGH);
        digitalWrite(IN13, LOW);
        digitalWrite(IN14, HIGH);

        digitalWrite(IN21, LOW);
        digitalWrite(IN22, HIGH);
        digitalWrite(IN23, LOW);
        digitalWrite(IN24, HIGH);
        break;

      case 'L': // Left turn
 digitalWrite(IN11, LOW);
        digitalWrite(IN12, HIGH);
        digitalWrite(IN13, HIGH);
        digitalWrite(IN14, LOW);
 digitalWrite(IN21, LOW);
        digitalWrite(IN22, HIGH);
        digitalWrite(IN23, HIGH);
        digitalWrite(IN24, LOW);

        // digitalWrite(IN11, LOW);
        // digitalWrite(IN12, HIGH);
        // digitalWrite(IN13, LOW);
        // digitalWrite(IN14, HIGH);

        // digitalWrite(IN21, HIGH);
        // digitalWrite(IN22, LOW);
        // digitalWrite(IN23, HIGH);
        // digitalWrite(IN24, LOW);
        break;

      case 'R': // Right turn
   digitalWrite(IN11, HIGH);
        digitalWrite(IN12, LOW);
        digitalWrite(IN13, LOW);
        digitalWrite(IN14, HIGH);
   digitalWrite(IN21, HIGH);
        digitalWrite(IN22, LOW);
        digitalWrite(IN23, LOW);
        digitalWrite(IN24, HIGH);

        // digitalWrite(IN11, HIGH);
        // digitalWrite(IN12, LOW);
        // digitalWrite(IN13, HIGH);
        // digitalWrite(IN14, LOW);

        // digitalWrite(IN21, LOW);
        // digitalWrite(IN22, HIGH);
        // digitalWrite(IN23, LOW);
        // digitalWrite(IN24, HIGH);
        break;

      case 'S': // Stop
        digitalWrite(IN11, LOW);
        digitalWrite(IN12, LOW);
        digitalWrite(IN13, LOW);
        digitalWrite(IN14, LOW);

        digitalWrite(IN21, LOW);
        digitalWrite(IN22, LOW);
        digitalWrite(IN23, LOW);
        digitalWrite(IN24, LOW);
        break;

      default:
        Serial.println("Invalid Command");
        break;
    }
  }
}
  
