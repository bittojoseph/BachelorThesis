/* 
 * rosserial Subscriber and Publisher fo Neptune
 *                  Ver.1.0 Written by Bitto Joseph
 *                  17.12.2020
 */

#define USE_USBCON

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include "MPU9250.h"
#include <Servo.h>
ros::NodeHandle  nh;

// Servo conigurations are ported from Arduino
// Only the ports are changed 
Servo servo_rudder;
Servo servo_elevator;
Servo water_pump;
Servo speed_control;
Servo camera_led;

// Define all the pins
#define pumpPin 3
#define speedPin 4
#define elevatorPin 5
#define rudderPin 6
#define batteryPinAhoi 20
#define batteryTrigPinAhoi 8
#define batteryPinMotors 21
#define batteryTrigPinMotors 7
#define pressurePin 22
#define temperatureBus 23 

/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(temperatureBus); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature Tsensors(&oneWire);

//imu object
MPU9250 mpu;

void servo_rudder_cb( const std_msgs::UInt16& cmd_msg){
  servo_rudder.attach(rudderPin); //attach it to pin 6 of teensy
  servo_rudder.write(cmd_msg.data); // 
  //servo_rudder.detach(); //detach from pin 6
}

void servo_elevator_cb( const std_msgs::UInt16& cmd_msg){
  servo_elevator.attach(elevatorPin); //attach it to pin 5 of teensy
  servo_elevator.write(cmd_msg.data); //   
  //servo_elevator.detach(); //detach from pin 9
}

void water_pump_cb( const std_msgs::UInt16& cmd_msg){
  water_pump.attach(pumpPin); //attach it to pin 3 of teensy
  if (cmd_msg.data >= 170){
    water_pump.write(170);
  }else{
  water_pump.write(cmd_msg.data); //
  }
  //water_pump.detach(); //detach from pin 11
}

void speed_control_cb( const std_msgs::UInt16& cmd_msg){
  speed_control.attach(speedPin); //attach it to pin 4 of teensy
  speed_control.write(cmd_msg.data); // 
  //speed_control.detach(); //detach from pin 10
}

// Led is not connected for the time being
/*
void camera_led_cb( const std_msgs::UInt16& cmd_msg){
  camera_led.attach(13); //attach it to pin 13
  camera_led.write(cmd_msg.data); //  
  //camera_led.detach(); //detach from pin 13
}
*/

ros::Subscriber<std_msgs::UInt16> sub_1("servo_rudder", servo_rudder_cb);
ros::Subscriber<std_msgs::UInt16> sub_2("servo_elevator", servo_elevator_cb);
ros::Subscriber<std_msgs::UInt16> sub_3("water_pump", water_pump_cb);
ros::Subscriber<std_msgs::UInt16> sub_4("speed_control", speed_control_cb);
// ros::Subscriber<std_msgs::UInt16> sub_5("camera_led", camera_led_cb);


std_msgs::Float32 temp_msg;
ros::Publisher pub_temp("temperature", &temp_msg);

std_msgs::Float32 pitch_msg;
ros::Publisher pub_pitch("pitch", &pitch_msg);

std_msgs::Float32 yaw_msg;
ros::Publisher pub_yaw("yaw", &yaw_msg);

std_msgs::UInt16 pressure_msg;
ros::Publisher pub_pressure("pressure", &pressure_msg);

std_msgs::UInt16 batteryMotor_msg;
ros::Publisher pub_batteryMotor("batteryMotors", &batteryMotor_msg);

std_msgs::UInt16 batteryAhoi_msg;
ros::Publisher pub_batteryAhoi("batteryAhoi", &batteryAhoi_msg);


void setup(){
  nh.initNode();
  nh.subscribe(sub_1);
  nh.subscribe(sub_2);
  nh.subscribe(sub_3);
  nh.subscribe(sub_4);
 //nh.subscribe(sub_5);

  // Publishers
  nh.advertise(pub_temp);
  nh.advertise(pub_pitch);
  nh.advertise(pub_yaw);
  nh.advertise(pub_pressure);
  nh.advertise(pub_batteryMotor);
  nh.advertise(pub_batteryAhoi);
  
  // Setup temperature sensor
  Tsensors.begin();

  // Setup IMU
  Wire.begin();
  mpu.setup(0x68);
  // Set Biases
  // void setAccBias(const uint8_t i, const float v) {
  //      if (i < 3) accelBias[i] = v;
  // }

  //servo_rudder.attach(6); //attach it to pin 6
  //servo_elevator.attach(9); //attach it to pin 9
  //water_pump.attach(11); //attach it to pin 11
  //speed_control.attach(10); //attach it to pin 10
  //camera_led.attach(13); //attach it to pin 13
}

unsigned long publisher_timer;

void loop(){
  if (millis() > publisher_timer) {
    // Publish temperature readings
    Tsensors.requestTemperatures(); // Send the command to get temperature
    temp_msg.data = Tsensors.getTempCByIndex(0);
    pub_temp.publish(&temp_msg);
  
    // publish pressure sensor readings
    pressure_msg.data = analogRead(pressurePin);
    pub_pressure.publish(&pressure_msg);

    if (mpu.update()) {
      // publish mpu values if available
      yaw_msg.data = mpu.getYaw();
      pub_yaw.publish(&yaw_msg);
      pitch_msg.data = mpu.getPitch();
      pub_pitch.publish(&pitch_msg);
    }  
    publisher_timer = millis() + 5; //publish once every 5 Millisecond
  }
  nh.spinOnce();
  delay(1); // Just for texting. Don't forget to take this away 
}
