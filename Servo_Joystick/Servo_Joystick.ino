/*
 * Servo_Joystick
 * Updated version of rosserial ServoControl Example
 *
 * This sketch demonstrates the control of servo
 * using ROS, the arduino, and a joystick
 *
 * Editor: Asmaa Al-Saggaf
 * Date: 8/12/2018
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <sensor_msgs/Joy.h>

ros::NodeHandle  nh;

Servo servo;
int pos = 0;

void servo_cb( const sensor_msgs::Joy& cmd_msg){
  if (cmd_msg.buttons[5] > 0){
    pos += 30;
    if (pos > 180) {pos = 180;}
    servo.write(pos); //set servo angle, should be from 0-180  
  }
    if (cmd_msg.buttons[4] > 0){
    pos -= 30;
    if (pos < 0) {pos = 0;}
    servo.write(pos); //set servo angle, should be from 0-180  
  } 
}


ros::Subscriber<sensor_msgs::Joy> sub("joy", servo_cb);

void setup(){
  pinMode(13, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
  
  servo.attach(9); //attach it to pin 9
}

void loop(){
  nh.spinOnce();
  delay(1);
}
