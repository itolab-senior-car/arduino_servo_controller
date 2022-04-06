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
  //reverse.write(msg.reverse);
}


void closestCallback(const std_msgs::Bool& judge_closest){
  if(judge_closest.data == 1)
  {
    reverse.write(40);//110°の角度にサーボモータを動かす前進
    //delay(100);

  }else if (judge_closest.data == 0){
    reverse.write(60);//60°の角度にサーボモータを動かす後退
    //delay(100);
  }
}



std_msgs::Float32 str_msg;
ros::Publisher chatter("potangle", &str_msg);
ros::Subscriber<itolab_senior_car_msgs::Servo> servo_sub("servo_cmd", servoCmdCallback);
ros::Subscriber<std_msgs::Bool> back_sub("judge_closest", closestCallback);//sokudowouketoru

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
  val = analogRead( analogPin ); //ピンの値を読み取り
//  if(val>0)
//  {
//    v_convert = (float)val  * 0.26393f; //読み取った値を角度に変換、floatで計算
//   
//
//    Serial.print( "value / volt : " ); //表示をプリント
//    Serial.print( val ); //読み取り値を表示
//    Serial.print( " / " ); //表示をプリント
//    Serial.println( v_convert ); //計算した電圧値を表示、改行
//
//
//     str_msg.data = v_convert;
//     chatter.publish (&str_msg);
//
////    nh.spinOnce();
////    delay(100);
//  }

  nh.spinOnce();
  delay(100);
}
  






//ros::Subscriber<std_msgs::Bool> back_sub("judge_closest", closestCallback);
 // if(judge_closest=True){
    
//   reverse.write(90);//90°の角度にサーボモータを動かす
//  delay(400);
// nh.spinOnce();
//   delay(100);
// } else {
// reverse.write(0);//0°の角度にサーボモータを動かす
// delay(400);
// nh.spinOnce();
// delay(100);
//}
 
