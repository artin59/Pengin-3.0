#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

float acceleration;
float rotational;
float jerk;
float force;

const int fsrpin = 2;  // Pin connected to the FSR
const float VCC = 3.3; // Voltage supplied to the FSR circuit
const float R = 10000; // Value of the fixed resistor in the voltage divider (10kΩ)

float previousAcceleration = 0;
unsigned long previousTime = 0;

Adafruit_MPU6050 mpu;

void setup(void) {
	Serial.begin(115200);

  pinMode(fsrpin, INPUT); // Set the FSR pin as an input

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

	delay(100);
}

void loop() {
	/* Get new sensor events with the readings */
	sensors_event_t a, g, temp;
	mpu.getEvent(&a, &g, &temp);

  acceleration = abs(sqrt(a.acceleration.x *a.acceleration.x + a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z)-9);
  rotational = sqrt(g.gyro.x *g.gyro.x + g.gyro.y * g.gyro.y + g.gyro.z * g.gyro.z);

  if (acceleration > 10000)
    acceleration = 0;
  
  if (rotational > 10000)
    rotational = 0;

  int rawValue = analogRead(fsrpin); // Read the raw analog value from the FSR
  float voltage = rawValue * (VCC / 4095.0); // Convert the raw value to voltage
  float fsrResistance = (VCC - voltage) * R / voltage; // Calculate the FSR resistance

  force = acceleration*pow(49683/fsrResistance ,1.4706);

  unsigned long currentTime = millis();
  float dt = (currentTime - previousTime) / 1000.0;

  if (previousTime != 0) { // Skip the first iteration
    jerk = abs((acceleration - previousAcceleration) / dt);
  }

  // Update previous acceleration and time
  previousAcceleration = acceleration;
  previousTime = currentTime;

  Serial.print(acceleration);
	Serial.println(" m/s^2");

  Serial.print(jerk);
  Serial.println("m/s^3");

  Serial.print(force);
  Serial.println("N");

	Serial.println("");
	delay(100);
}