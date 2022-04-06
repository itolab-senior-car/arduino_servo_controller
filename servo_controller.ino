#include <ros.h>
//#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <Servo.h> 
#include <std_msgs/Bool.h>
#include "itolab_senior_car_msgs/Servo.h"

ros::NodeHandle nh;

Servo steering;
Servo accel;
Servo reverse;


void servoCmdCallback(const itolab_senior_car_msgs::Servo& msg){
  steering.write(msg.steering);
  accel.write(msg.accel); 
}

void closestCallback(const std_msgs::Bool& judge_closest){
  if(judge_closest.data == 1)
  {
    reverse.write(40);//40°の角度にサーボモータを動かす前進
    //delay(100);

  }else if (judge_closest.data == 0){
    reverse.write(60);//60°の角度にサーボモータを動かす後退
    //delay(100);
  }
}



std_msgs::Float32 str_msg;
ros::Publisher chatter("potangle", &str_msg);
ros::Subscriber<itolab_senior_car_msgs::Servo> servo_sub("servo_cmd", servoCmdCallback);
ros::Subscriber<std_msgs::Bool> back_sub("judge_closest", closestCallback); //judge_closestトピックが1だったら前進, judge_closetトピックが0だったら後退にする

int analogPin =3; //アナログ入力ピンを３番に設定
int val = 0; //読み取り値の変数設定
float v_convert = 0.0f; //計算値の変数設定、オーバーフローしないようにflaot設定


void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  Serial.begin(57600); //シリアル通信のデータ転送レートを9600bpsで指定。bpsはビット/秒。
  steering.attach(9); //attach it to pin 9
  accel.attach(10);//attach it to pin10
  reverse.attach(7);//attach it to pin7

  reverse.write(40);
  
  nh.getHardware()->setBaud(57600);
  Serial.begin(57600);
  
  nh.subscribe(servo_sub);
  nh.subscribe(back_sub);
}


void loop()
{
  nh.spinOnce();
  delay(100);
}
  

 
