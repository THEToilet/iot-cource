/*
Wire.h
I2C通信（Wireクラス）
2線による通信を行うためのI2C通信ライブラリです。Wireと呼ばれることもあります。
*/
#include<Wire.h>
#include<Arduino.h>
#include<Adafruit_PWMServoDriver.h>
#include "IRremote.h" // 赤外線送受信用ヘッダファイル
#include "CppList.h"

#define BEAT 100   // 音の長さを指定
#define PINNO 12   // 圧電スピーカを接続したピン番号

#define ServoMin 100//サーボの曲がる最小角度
#define ServoMax 500//サーボの曲がる最大角度

//PCA9685のI2cに使うアドレスは0x40
//TwoWireインタフェース上のI2Cアドレスを使用して、新しいPCA9685 PWMドライバチップをインスタンス化します。
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int rcv_count;
IRrecv **all_rcv;

bool _initialized = false;

int ServoDragonCh = 15;
int ServoOrcCh = 14;
int ServoGorlemCh = 13;
int ServoZombieCh = 12;
int ServoGirlCh = 11;

int DragonN = 0;
int OrcN = 0;
int GorlemN = 0;
int ZombieN = 0;
int GirlN = 0;


int ang = 20;
  
void setup() 
{

  if (_initialized) return;
  // put your setup code here, to run once:
  pwm.begin();
  pwm.setPWMFreq(50);
  Serial.begin(9600);


  ServoMove(ServoDragonCh,ang);
  ServoMove(ServoOrcCh,ang);
  ServoMove(ServoGorlemCh,ang);
  ServoMove(ServoZombieCh,ang);
  ServoMove(ServoGirlCh,ang);
 
  rcv_count = 5;
  all_rcv = (IRrecv **)malloc(rcv_count*sizeof(int));
  all_rcv[0] = new IRrecv(3);
  all_rcv[1] = new IRrecv(4);
  all_rcv[2] = new IRrecv(7);
  all_rcv[3] = new IRrecv(8);
  all_rcv[4] = new IRrecv(11);
  
  for (int i=0; i<rcv_count; i++){
    all_rcv[i]->enableIRIn(); //構造体配列のポインタ表現?
  }
  
  _initialized = true;
}

  
void loop() 
{
  decode_results results;
  // put your main code here, to run repeatedly:
/*
  //Dragonの処理
  if (all_rcv[4]->decode(&results))
  {
        Serial.print("It's 11!  ");
        ang=50;
        ServoMove(ServoDragonCh,ang);
        Serial.println(results.value, HEX);
        all_rcv[4]->resume();
        DragonN++;
/*      
      tone(PINNO,262,BEAT) ; //ド
      delay(BEAT) ;
      tone(PINNO,294,BEAT) ; //レ
      delay(BEAT) ;
      tone(PINNO,330,BEAT) ; //ミ
      delay(BEAT) ;
      tone(PINNO,349,BEAT) ; //ファ
      delay(BEAT) ;
      tone(PINNO,392,BEAT) ; //ソ
      delay(BEAT) ;
      tone(PINNO,440,BEAT) ; //ラ
      delay(BEAT) ;
      tone(PINNO,494,BEAT) ; //シ
      delay(BEAT) ;
      tone(PINNO,523,BEAT) ; //ド
       
  }
  */
/*
  
  //Orcの処理
  if (all_rcv[3]->decode(&results)) 
    {
        Serial.print("It's 8!  ");
        ang=50;
        ServoMove(ServoOrcCh,ang);
        Serial.println(results.value, HEX);
        all_rcv[3]->resume();
        OrcN++;
/*      
      tone(PINNO,262,BEAT) ; //ド
      delay(BEAT) ;
      tone(PINNO,294,BEAT) ; //レ
      delay(BEAT) ;
      tone(PINNO,330,BEAT) ; //ミ
      delay(BEAT) ;
      tone(PINNO,349,BEAT) ; //ファ
      delay(BEAT) ;
      tone(PINNO,392,BEAT) ; //ソ
     
      
    }
  *?
    /*
  //Gorlemの処理
    if (all_rcv[2]->decode(&results)) 
    {
        Serial.print("It's 7!  ");
        ang=50;
        ServoMove(ServoGorlemCh,ang);
        Serial.println(results.value, HEX);
        all_rcv[2]->resume();
        GorlemN++;
    /*  
      tone(PINNO,262,BEAT) ; //ド
      delay(BEAT) ;
      tone(PINNO,294,BEAT) ; //レ
      delay(BEAT) ;
      tone(PINNO,330,BEAT) ; //ミ
      delay(BEAT) ;
      tone(PINNO,349,BEAT) ; //ファ
      delay(BEAT) ;
      tone(PINNO,392,BEAT) ; //ソ
      
       
    }
*/

  //Zombieの処理
   if (all_rcv[1]->decode(&results)) 
    {
        Serial.print("It's 1!  ");  
        ang=ang+10;
        if(ang>=170)ang=0;
        ServoMove(ServoZombieCh,ang);
        ServoMove(ServoGirlCh,ang);
        ServoMove(ServoGorlemCh,ang);
        ServoMove(ServoOrcCh,ang);
        ServoMove(ServoDragonCh,ang);
        all_rcv[1]->resume();
        delay(500);     
      /*
      tone(PINNO,262,BEAT) ; //ド
      delay(BEAT) ;
      tone(PINNO,294,BEAT) ; //レ
      delay(BEAT) ;
      tone(PINNO,330,BEAT) ; //ミ
      delay(BEAT) ; 
      */  
     }
   
  /*
  //Girlの処理
  if (all_rcv[1]->decode(&results)) 
    {
        Serial.print("It's 0!  ");
        ang=50;
        ServoMove(ServoGirlCh,ang);
        Serial.println(results.value, HEX);
        all_rcv[1]->resume();
        GirlN++;
      /*
      tone(PINNO,262,BEAT) ; //ド
      delay(BEAT);
      tone(PINNO,294,BEAT) ; //レ
      delay(BEAT);
      tone(PINNO,330,BEAT) ; //ミ
      delay(BEAT);
      
      }
   */ 
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
  変換後の数値 (long)
  */  
  ang = map(ang,0,180,ServoMin,ServoMax);
  //角度（0～180）をPWMのパルス幅（150～500）に変換
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
