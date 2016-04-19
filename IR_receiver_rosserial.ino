#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Vector3.h>

#define LOOPTIME        100

ros::NodeHandle nh;
//std_msgs::UInt16 irValue;
geometry_msgs::Vector3 irValue;
ros::Publisher pub("irValue", &irValue);
unsigned long lastMilli = 0;

void setup() {
  nh.initNode();
  nh.advertise(pub);
  Serial.begin(57600);
  
}

void loop() {
  if ((millis()-lastMilli) >= LOOPTIME)   {        // enter timed loop
    lastMilli = millis();
    irValue.x = analogRead(A0);
    irValue.y = analogRead(A1);
    pub.publish(&irValue);

  }
    nh.spinOnce();

}
