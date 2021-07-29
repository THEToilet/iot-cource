#include "Arduino.h"
#include "SoftwareSerial.h"
#include <PCA9685.h>     //PCA9685用ヘッダーファイル
PCA9685 pwm = PCA9685(0x41);    //PCA9685のアドレス指定（アドレスジャンパ未接続時）
#include <SoftwareSerial.h>

#define SERVOMIN 150            //最小パルス幅 (GWS Micro2BBMG)
#define SERVOMAX 500            //最大パルス幅 (GWS Micro2BBMG)
#define SERVO_CH 0

void setup() {
 pwm.begin();                   //初期設定 (アドレス0x40用)
 pwm.setPWMFreq(50);            //PWM周期を50Hzに設定 (アドレス0x40用)
}

int n=0;

void loop() {
  servo_write(SERVO_CH, n);
  n=n+10;
  if(n>=180){
    n=0;
  }
  delay(500);  
}

void servo_write(int ch, int ang){ //動かすサーボチャンネルと角度を指定
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～500）に変換
  pwm.setPWM(ch, 0, ang);
}
