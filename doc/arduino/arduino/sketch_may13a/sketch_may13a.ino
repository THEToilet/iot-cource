#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 150
#define SERVOMAX 600
#define CENTER 375
int target = 0;
float movetopos;
char cmd;
 
void setup() {
 Serial.begin(9600);
 pwm.begin();
 pwm.setPWMFreq(60);
 for (int i=0;i<16;i++)
 pwm.setPWM(i,0,CENTER);
 Serial.println("Ready [t###]/[m####]");
}
 
void loop() {
 if (Serial.available()){
  int pwmValue;
  cmd = Serial.read();
  movetopos = Serial.parseInt();
  if (cmd == 't'){
   target = movetopos;
   Serial.print("target ");
   Serial.println(target);
  }else if (cmd == 'm'){
   Serial.print("move ");
   Serial.println(movetopos);
   pwmValue = map(0,10,180,SERVOMIN,SERVOMAX);
   pwm.setPWM(0, 0, pwmValue);
  }
 }
}

  
