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
#include <std_msgs/Bool.h>

ros::NodeHandle  nh;

Servo servo;
int pos = 0;

void servo_cb( const std_msgs::Bool& cmd_msg){
  if (cmd_msg.data == true){
    pos += 30;
    if (pos > 180) {pos = 0;}
    servo.write(pos); //set servo angle, should be from 0-180  
    digitalWrite(13, HIGH-digitalRead(13));  //toggle led
  } 
}


ros::Subscriber<std_msgs::Bool> sub("pushed", servo_cb);

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
