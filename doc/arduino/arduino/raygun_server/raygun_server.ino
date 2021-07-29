/*
Wire.h
I2C通信（Wireクラス）
2線による通信を行うためのI2C通信ライブラリです。Wireと呼ばれることもあります。
*/
#include<Wire.h>
#include<Adafruit_PWMServoDriver.h>
#include <IRremote.h>

#define ServoMin 100
#define ServoMax 500
//PCA9685のアドレスは0x40
//TwoWireインタフェース上のI2Cアドレスを使用して、新しいPCA9685 PWMドライバチップをインスタンス化します。
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

IRrecv irrecv(11);
decode_results results;

int SERVO_CH = 0;
int ang = 0;
  
void setup() 
{
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(50);
  Serial.begin(9600);
  irrecv.enableIRIn();
  ServoMove(SERVO_CH,ang);

}

  
void loop() 
{
  // put your main code here, to run repeatedly:

  if (irrecv.decode(&results)) {
    if (results.decode_type == SONY) Serial.print("It's SONY!  ");
    ang=170;
    ServoMove(SERVO_CH,ang);
    Serial.println(results.value, HEX);
    irrecv.resume();
    delay(100);
  }
//  else
//  {
//    ang = 0;
//    ServoMove(SERVO_CH,ang);
//  }

  delay(100);
  
}

void ServoMove(int ch , int ang)
{
/*map(value, fromLow, fromHigh, toLow, toHigh)
    【パラメータ】 
  value: 変換したい数値 
  fromLow: 現在の範囲の下限 
  fromHigh: 現在の範囲の上限 
  toLow: 変換後の範囲の下限 
  toHigh: 変換後の範囲の上限 
     【戻り値】 
  変換後の数値 (long)*/ 
  ang = map(ang, 0, 180, ServoMin, ServoMax);  //角度（0～180）をPWMのパルス幅（150～500）に変換
/*

void Adafruit_PWMServoDriver::setPWM  ( uint8_t   num,
uint16_t  on,
uint16_t  off 
)   
Sets the PWM output of one of the PCA9685 pins.

Parameters
num One of the PWM output pins, from 0 to 15
on  At what point in the 4096-part cycle to turn the PWM output ON
off At what point in the 4096-part cycle to turn the PWM output OFF

 */
  pwm.setPWM(ch, 0, ang);

  
}
