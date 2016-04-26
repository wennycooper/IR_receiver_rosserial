#include <ros.h>
#include <std_msgs/UInt16.h>
#include <geometry_msgs/Vector3.h>

#define LOOPTIME1         10
unsigned long lastMilli1 = 0;

#define LOOPTIME2        1000
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
 unsigned int i=0;
unsigned lastTime = 0;
void loop() {
  //lastTime = millis();
  for (i=0; i<100; i++) {
    irValue.x += analogRead(A0);
    irValue.y += analogRead(A1);  
  }
//  Serial.println(millis() - lastTime);

  irValue.x = irValue.x/100;
  irValue.y = irValue.y/100;

// publish and clean up //  
  pub.publish(&irValue);
  irValue.x = 0;
  irValue.y = 0;  
  
/*
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

*/
    nh.spinOnce();

}

