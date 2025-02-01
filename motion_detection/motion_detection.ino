#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

long acceleration;
long rotational;

Adafruit_MPU6050 mpu;

void setup(void) {
	Serial.begin(115200);

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

  acceleration = sqrt(a.acceleration.x *a.acceleration.x + a.acceleration.y * a.acceleration.y + a.acceleration.z + a.acceleration.z);
  rotational = sqrt(g.gyro.x *g.gyro.x + g.gyro.y * g.gyro.y + g.gyro.z + g.gyro.z);

  if (acceleration > 10000)
    acceleration = 0;
  
  if (rotational > 10000)
    rotational = 0;

	/* Print out the values */
	// Serial.print("Acceleration X: ");
	// Serial.print(a.acceleration.x);
	// Serial.print(", Y: ");
	// Serial.print(a.acceleration.y);
	// Serial.print(", Z: ");
	// Serial.print(a.acceleration.z);
  Serial.print(acceleration);
	Serial.println(" m/s^2");

	// Serial.print("Rotation X: ");
	// Serial.print(g.gyro.x);
	// Serial.print(", Y: ");
	// Serial.print(g.gyro.y);
	// Serial.print(", Z: ");
	// Serial.print(g.gyro.z);
  Serial.print(rotational);
	Serial.println(" rad/s");


	Serial.println("");
	delay(100);
}