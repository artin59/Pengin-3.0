#include "Wire.h"
#include <WiFi.h>
#include <WebServer.h>

// Wi-Fi credentials (replace with your phone's hotspot details)
const char* ssid = "Ishaan";
const char* password = "14165563809";

// MPU-6050 settings
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
const float ACCEL_SENSITIVITY = 4096.0; // LSB/g for ±2g setting

int16_t ax_raw, ay_raw, az_raw; // Raw accelerometer data
float ax, ay, az, total_accel; // Acceleration in g

// Create a web server on port 80
WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.println(WiFi.localIP()); // Print the IP address of the ESP32

  // Initialize MPU-6050
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU-6050
  Wire.endTransmission(true);

  // Set up web server routes
  server.on("/", handleRoot); // Serve the HTML page
  server.on("/data", handleData); // Serve sensor data as JSON

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Read accelerometer data
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // ACCEL_XOUT_H register
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true); // Read 6 bytes

  ax_raw = Wire.read() << 8 | Wire.read(); // X-axis
  ay_raw = Wire.read() << 8 | Wire.read(); // Y-axis
  az_raw = Wire.read() << 8 | Wire.read(); // Z-axis

  // Convert raw values to g-force
  ax = ax_raw / ACCEL_SENSITIVITY;
  ay = ay_raw / ACCEL_SENSITIVITY;
  az = az_raw / ACCEL_SENSITIVITY;

  // Calculate total acceleration magnitude
  total_accel = sqrt(ax * ax + ay * ay + az * az);

  // Print values
  Serial.print("aX = "); Serial.print(ax, 2);
  Serial.print(" | aY = "); Serial.print(ay, 2);
  Serial.print(" | aZ = "); Serial.print(az, 2);
  Serial.print(" | Total Accel = "); Serial.print(total_accel, 2);
  Serial.println(" g");

  delay(100);
}

// Serve the HTML page
void handleRoot() {
  String html = R"=====(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 MPU-6050 Data</title>
  <style>
    body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }
    .data { font-size: 1.5em; margin: 10px; }
  </style>
  <script>
    function fetchData() {
      fetch("/data")
        .then(response => response.json())
        .then(data => {
          document.getElementById("ax").innerText = data.ax.toFixed(2);
          document.getElementById("ay").innerText = data.ay.toFixed(2);
          document.getElementById("az").innerText = data.az.toFixed(2);
          document.getElementById("total").innerText = data.total.toFixed(2);
        });
    }
    setInterval(fetchData, 500); // Update data every 500ms
  </script>
</head>
<body>
  <h1>MPU-6050 Sensor Data</h1>
  <div class="data">aX: <span id="ax">0.00</span> g</div>
  <div class="data">aY: <span id="ay">0.00</span> g</div>
  <div class="data">aZ: <span id="az">0.00</span> g</div>
  <div class="data">Total Acceleration: <span id="total">0.00</span> g</div>
</body>
</html>
)=====";
  server.send(200, "text/html", html);
}

// Serve sensor data as JSON
void handleData() {
  String json = "{\"ax\":" + String(ax, 2) + 
                ",\"ay\":" + String(ay, 2) + 
                ",\"az\":" + String(az, 2) + 
                ",\"total\":" + String(total_accel, 2) + "}";
  server.send(200, "application/json", json);
}