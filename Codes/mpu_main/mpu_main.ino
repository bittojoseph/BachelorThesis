#include "MPU9250.h"

MPU9250 mpu;
void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);

    mpu.setup(0x68);  // change to your own address
}

void loop() {
  if (mpu.update()) {
      Serial.println(String(mpu.getAccX(), 4)+" "+String(mpu.getAccY(), 4)+" "+ String(mpu.getAccZ(), 4));
  }
}
