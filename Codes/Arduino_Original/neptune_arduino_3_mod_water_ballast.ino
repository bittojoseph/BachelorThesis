
/* 
 * rosserial Subscriber for Neptune
 */

#define USE_USBCON
/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle  nh;

Servo servo_rudder;
Servo servo_elevator;
Servo water_pump;
Servo speed_control;
Servo camera_led;

void servo_rudder_cb( const std_msgs::UInt16& cmd_msg){
  servo_rudder.attach(6); //attach it to pin 6
  servo_rudder.write(cmd_msg.data); // 
  //servo_rudder.detach(); //detach from pin 6
}

void servo_elevator_cb( const std_msgs::UInt16& cmd_msg){
  servo_elevator.attach(9); //attach it to pin 9
  servo_elevator.write(cmd_msg.data); //   
  //servo_elevator.detach(); //detach from pin 9
}

void water_pump_cb( const std_msgs::UInt16& cmd_msg){
  water_pump.attach(11); //attach it to pin 11
  if (cmd_msg.data >= 170){
    water_pump.write(170);
  }else{
  water_pump.write(cmd_msg.data); //
  }
  //water_pump.detach(); //detach from pin 11
}

void speed_control_cb( const std_msgs::UInt16& cmd_msg){
  speed_control.attach(10); //attach it to pin 10
  speed_control.write(cmd_msg.data); // 
  //speed_control.detach(); //detach from pin 10  
}

void camera_led_cb( const std_msgs::UInt16& cmd_msg){
  camera_led.attach(13); //attach it to pin 13
  camera_led.write(cmd_msg.data); //  
  //camera_led.detach(); //detach from pin 13
}

ros::Subscriber<std_msgs::UInt16> sub_1("servo_rudder", servo_rudder_cb);
ros::Subscriber<std_msgs::UInt16> sub_2("servo_elevator", servo_elevator_cb);
ros::Subscriber<std_msgs::UInt16> sub_3("water_pump", water_pump_cb);
ros::Subscriber<std_msgs::UInt16> sub_4("speed_control", speed_control_cb);
ros::Subscriber<std_msgs::UInt16> sub_5("camera_led", camera_led_cb);

void setup(){
  nh.initNode();
  nh.subscribe(sub_1);
  nh.subscribe(sub_2);
  nh.subscribe(sub_3);
  nh.subscribe(sub_4);
  nh.subscribe(sub_5);
  
  //servo_rudder.attach(6); //attach it to pin 6
  //servo_elevator.attach(9); //attach it to pin 9
  //water_pump.attach(11); //attach it to pin 11
  //speed_control.attach(10); //attach it to pin 10
  //camera_led.attach(13); //attach it to pin 13
}

void loop(){
  nh.spinOnce();
  delay(1);
}
