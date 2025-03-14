#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "your-SSID";       // Replace with your WiFi SSID
const char* password = "your-PASSWORD"; // Replace with your WiFi password

WebServer server(80);

bool led1State = false;
bool led2State = false;

void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT); // LED 1 (built-in LED)
    pinMode(2, OUTPUT);           // LED 2 (GPIO 2)

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP());

    // Serve the webpage
    server.on("/", HTTP_GET, []() {
        String html = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Home Automation Control</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f4f4f4;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        .container {
            background-color: #fff;
            padding: 20px;
            border-radius: 10px;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
            text-align: center;
        }
        h1 {
            margin-bottom: 20px;
        }
        .controls {
            margin-bottom: 20px;
        }
        button {
            padding: 10px 20px;
            margin: 5px;
            border: none;
            border-radius: 5px;
            background-color: #007bff;
            color: white;
            cursor: pointer;
            font-size: 16px;
        }
        button:hover {
            background-color: #0056b3;
        }
        .status {
            margin-top: 20px;
        }
        #led1-status, #led2-status {
            font-weight: bold;
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Home Automation Control</h1>
        <div class="controls">
            <button id="led1-on">Turn LED 1 ON</button>
            <button id="led1-off">Turn LED 1 OFF</button>
            <button id="led2-on">Turn LED 2 ON</button>
            <button id="led2-off">Turn LED 2 OFF</button>
        </div>
        <div class="status">
            <h2>Status:</h2>
            <p id="led1-status">LED 1: OFF</p>
            <p id="led2-status">LED 2: OFF</p>
        </div>
    </div>
    <script>
        document.getElementById('led1-on').addEventListener('click', function() {
            sendRequest('/led1/on');
            document.getElementById('led1-status').innerText = 'LED 1: ON';
        });

        document.getElementById('led1-off').addEventListener('click', function() {
            sendRequest('/led1/off');
            document.getElementById('led1-status').innerText = 'LED 1: OFF';
        });

        document.getElementById('led2-on').addEventListener('click', function() {
            sendRequest('/led2/on');
            document.getElementById('led2-status').innerText = 'LED 2: ON';
        });

        document.getElementById('led2-off').addEventListener('click', function() {
            sendRequest('/led2/off');
            document.getElementById('led2-status').innerText = 'LED 2: OFF';
        });

        function sendRequest(endpoint) {
            fetch(endpoint)
                .then(response => response.text())
                .then(data => console.log(data))
                .catch(error => console.error('Error:', error));
        }
    </script>
</body>
</html>
)=====";
        server.send(200, "text/html", html);
    });

    // Handle LED control requests
    server.on("/led1/on", HTTP_GET, []() {
        digitalWrite(LED_BUILTIN, HIGH);
        led1State = true;
        server.send(200, "text/plain", "LED 1 ON");
    });

    server.on("/led1/off", HTTP_GET, []() {
        digitalWrite(LED_BUILTIN, LOW);
        led1State = false;
        server.send(200, "text/plain", "LED 1 OFF");
    });

    server.on("/led2/on", HTTP_GET, []() {
        digitalWrite(2, HIGH);
        led2State = true;
        server.send(200, "text/plain", "LED 2 ON");
    });

    server.on("/led2/off", HTTP_GET, []() {
        digitalWrite(2, LOW);
        led2State = false;
        server.send(200, "text/plain", "LED 2 OFF");
    });

    // Start the server
    server.begin();
    Serial.println("HTTP server started");
}

void loop() {
    server.handleClient(); // Handle client requests
}