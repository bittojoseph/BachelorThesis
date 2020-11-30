#include "MPU9250.h"

MPU9250 mpu;
float xAxis, yAxis, zAxis;
void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address
}

void loop() {
  if (mpu.update()) {
      xAxis = mpu.getAccX();
      yAxis = mpu.getAccY();
      zAxis = mpu.getAccZ();
      Serial.println(String(xAxis, 4)+" "+String(yAxis, 4)+" "+ String(zAxis, 4));
  }
}