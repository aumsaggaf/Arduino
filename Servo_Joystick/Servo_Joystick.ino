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
