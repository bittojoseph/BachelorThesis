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
      Serial.println("p:" + String(mpu.getPitch(), 4)+"y:"+String(mpu.getYaw(), 4));
  }
}
