#include <Arduino.h>
#include "MPU9250.h"

MPU9250 mpu;

void setup()
{                                     
    Serial.begin(9600);

    Wire.begin();

    delay(2000);
    mpu.setup();
}

void loop()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 10)
    {
        mpu.update();
        
        int xAcc = (int) -1000 * mpu.getAccX();
        int yAcc = (int) -1000 * mpu.getAccY();
        int zAcc = (int) -1000 * mpu.getAccZ();

        String toSend = String(xAcc)+ " " + String(yAcc)+ " "+ String(zAcc);
        Serial.println(toSend);
        prev_ms = millis();
    }
}