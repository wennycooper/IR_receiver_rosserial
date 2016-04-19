#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Vector3.h>

#define LOOPTIME1         10
unsigned long lastMilli1 = 0;

#define LOOPTIME2        100
unsigned long lastMilli2 = 0;



ros::NodeHandle nh;
//std_msgs::UInt16 irValue;
geometry_msgs::Vector3 irValue;
ros::Publisher pub("irValue", &irValue);


void setup() {
  nh.initNode();
  nh.advertise(pub);
  Serial.begin(57600);
  
}

void loop() {
  if ((millis()-lastMilli1) >= LOOPTIME1)   {  // time to read ADC
    lastMilli1 = millis();

    // accumulate those readings
    irValue.x += analogRead(A0);
    irValue.y += analogRead(A1);
    //pub.publish(&irValue);

  }
  
  if ((millis()-lastMilli2) >= LOOPTIME2)   {  // time to pub
    lastMilli2 = millis();
    //irValue.x = analogRead(A0);
    //irValue.y = analogRead(A1);
    pub.publish(&irValue);
    irValue.x = 0;
    irValue.y = 0;
  }
    nh.spinOnce();

}
