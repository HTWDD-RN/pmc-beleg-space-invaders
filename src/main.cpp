#include "Arduino.h"
#include <TFT.h>
#include <SPI.h>
#include <Wire.h>

#include <Enemy.h>
#include <Player.h>

#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif

#define cs 10
#define dc 9
#define rst 8
#define numEnemy 3

//gyro
//https://howtomechatronics.com/tutorials/arduino/arduino-and-mpu6050-accelerometer-and-gyroscope-tutorial/
const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;

//game
TFT myScreen = TFT(cs, dc, rst);
Enemy e[numEnemy];
//Enemy e = Enemy(10, 10);
Player p = Player(50, 50);
int offset = 0;
int playerOffset = 0;
bool direction = true;

void readSensor();

void setup() {
	Serial.begin(115200);
	Serial.println("beginning tft setup");
	myScreen.begin();
    myScreen.background(0,0,0);
	myScreen.setTextSize(2);

	//gyro init
	
	Wire.begin();                      // Initialize comunication
	Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
	Wire.write(0x6B);                  // Talk to the register 6B
	Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
	Wire.endTransmission(true);        //end the transmission

	// // Configure Accelerometer Sensitivity - Full Scale Range (default +/- 2g)
	Wire.beginTransmission(MPU);
	Wire.write(0x1C);                  //Talk to the ACCEL_CONFIG register (1C hex)
	Wire.write(0x10);                  //Set the register bits as 00010000 (+/- 8g full scale range)
	Wire.endTransmission(true);
	// Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)
	Wire.beginTransmission(MPU);
	Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
	Wire.write(0x10);                   // Set the register bits as 00010000 (1000deg/s full scale)
	Wire.endTransmission(true);

	for(int i = 0; i < 5; i++){
		e[i] = Enemy(10+i*20, 10);
	}
	for(int i = 0; i < numEnemy; i++){
		e[i].render();
		e[i].draw(myScreen);
	}
	p.draw(myScreen);
}

void loop() {
	readSensor();

	if (AccX < -0.05f) {
		Serial.println("links");
		playerOffset--;
	}

	if (AccX > 0.05f) {
		Serial.println("rechts");
		playerOffset++;
	}

	//e.moveTo(10 + offset/8, 10, myScreen);
	for(int i = 0; i < numEnemy; i++){
		e[i].moveTo(10 + i * 20 + offset / 4, 10, myScreen);
	}
	Serial.println(offset);
	delay(10);
	if (direction) {
		offset++;
	}else {
		offset--;
	}
	p.moveTo(50+playerOffset, 80, myScreen);
	Serial.println(playerOffset);

	//dont let the player go outside the screen area
	if (playerOffset > 110) {
		playerOffset = 110;
	}
	if (playerOffset < -50) {
		playerOffset = -50;
	}

	if (offset > 300 || offset < 0) {
		direction = !direction;
	}
}

void readSensor(){
	Wire.beginTransmission(MPU);
	Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
	//For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
	AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
	AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
	AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
	// Calculating Roll and Pitch from the accelerometer data
	accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58) See the calculate_IMU_error()custom function for more details
	accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)
	Serial.print("accx: ");
	Serial.print(AccX);

	previousTime = currentTime;        // Previous time is stored before the actual time read
	currentTime = millis();            // Current time actual time read
	elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
	Wire.beginTransmission(MPU);
	Wire.write(0x43); // Gyro data first register address 0x43
	Wire.endTransmission(false);
	Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
	GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
	GyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
	GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;
	//Serial.print(" gyrox: ");
	//Serial.println(GyroX);
}
