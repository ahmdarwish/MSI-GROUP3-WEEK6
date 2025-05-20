#include <Wire.h>
const int MPU = 0x68; // I2C address of MPU6050

void setup() {
  Serial.begin(9600);   // PLX-DAQ default baud rate
  Wire.begin();

  // Wake up the MPU6050
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // Wake up MPU6050
  Wire.endTransmission(true);

  // PLX-DAQ setup
  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Temperature(C)");
}

void loop() {
  // Read temperature registers
  Wire.beginTransmission(MPU);
  Wire.write(0x41); // Starting register for temperature
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 2, true);

  int16_t rawTemp = Wire.read() << 8 | Wire.read();
  float tempC = (rawTemp / 340.0) + 36.53; // Datasheet formula

  // Send data to PLX-DAQ
  Serial.print("DATA,TIME,");
  Serial.println(tempC, 2); // 2 decimal places

  delay(1000); // 1 reading per second
}