#include<Wire.h>
#include<Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 150
#define SERVOMAX 600
#define CENTER 375

void setup(){
  pwm.begin();
  pwm.setPWMFreq(60);
}

void loop(){
    int angle = 180;
    angle = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(0,0,angle);
}
