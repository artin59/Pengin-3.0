#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <WiFi.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

const char* ssid = "name";
const char* password = "pass";

WebSocketsServer webSocket = WebSocketsServer(80);


float acceleration;
float rotational;
float jerk;
float force;


const int fsrPins[4] = {34, 35, 32, 33};
const float VCC = 3.3; // Voltage supplied to the FSR circuit
const float R = 10000; // Value of the fixed resistor in the voltage divider (10kÎ©)

float previousAcceleration = 0;
unsigned long previousTime = 0;

Adafruit_MPU6050 mpu;


void webSocketEvent (uint8_t num, WStype_t type, uint8_t* payload, size_t lenght){

  switch(type){
    case WStype_CONNECTED:
      Serial.println("Client Connected");
      break;
    case WStype_DISCONNECTED:
      Serial.println("Client Disconencted");
      break;
  }
}

void sendSensorData(float jerk, float weight[4]){

  StaticJsonDocument<200> jsonDoc;

  jsonDoc["jerk"] = jerk;

  JsonArray array = jsonDoc.createNestedArray("forces");
  for (int i = 0; i < 4; i++){
    array.add(weight[i]);
  }

  String jsonString ="";
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);
  webSocket.broadcastTXT(jsonString);

}


void setup(void) {
	Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.println(WiFi.localIP()); // Print the IP address of the ESP32

    
  for (int i = 0; i < 4; i++) {
      pinMode(fsrPins[i], INPUT);
  }

	// Try to initialize!
	if (!mpu.begin()) {
		Serial.println("Failed to find MPU6050 chip");
		while (1) {
		  delay(10);
		}
	}
	Serial.println("MPU6050 Found!");

	// set accelerometer range to +-8G
	mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

	// set gyro range to +- 500 deg/s
	mpu.setGyroRange(MPU6050_RANGE_500_DEG);

	// set filter bandwidth to 21 Hz
	mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

	delay(100);
}


void loop() {

  webSocket.loop();
  float weight[4];


	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

  acceleration = abs(sqrt(a.acceleration.x *a.acceleration.x + a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)-9);
  rotational = sqrt(g.gyro.x *g.gyro.x + g.gyro.y * g.gyro.y + g.gyro.z * g.gyro.z);

  if (acceleration > 10000)
    acceleration = 0;
  
  if (rotational > 10000)
    rotational = 0;

  for (int i = 0; i < 4; i++) {
    int rawValue = analogRead(fsrPins[i]); // Read the raw analog value from the FSR
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.print(rawValue);
    // Serial.println("N");    
    float voltage = rawValue * (VCC / 4095.0); // Convert the raw value to voltage
    float fsrResistance = (VCC - voltage) * R / voltage; // Calculate the FSR resistance
    float force = (1000.0 / fsrResistance) * 1000.0; 
    //force = acceleration*pow(49683/fsrResistance ,1.4706);
    weight[i] = force;

   }

  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0;

  if (previousTime != 0) { // Skip the first iteration
    jerk = abs((acceleration - previousAcceleration) / dt);
  }

  // Update previous acceleration and time
  previousAcceleration = acceleration;
  previousTime = currentTime;

  sendSensorData(jerk, weight);

  // Serial.print(acceleration);
	// Serial.println(" m/s^2");

  // Serial.print(jerk);;
  // Serial.println("m/s^3");

  // for (int i = 0; i < 4; i++) {
  //   Serial.print(i);
  //   Serial.print(": ");
  //   Serial.print(weight[i]);
  //   Serial.println("N");
  //  }



	Serial.println("");
	delay(200);
}