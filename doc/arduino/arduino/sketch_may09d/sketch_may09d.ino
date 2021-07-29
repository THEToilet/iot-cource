#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// ボタンに繋がるピン
#define BUTTON 19
// SoftwareSerialのRX, TXピン
#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int numfile;   //楽曲ファイル数
int lastval=0; //ボタンの値保存用

void setup()
{
  pinMode(BUTTON, INPUT);
  randomSeed(analogRead(0)); 
  
  // SoftwareSerialとDFPlayerの初期化
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    while(true);
  }

  myDFPlayer.volume(25);  // 音量の設定(0～30)
  numfile = myDFPlayer.readFileCounts(DFPLAYER_DEVICE_SD); //音楽ファイル数取得
}

void loop()
{
  lastval = (lastval << 1) | digitalRead(BUTTON); // チャタリング回避
  if(lastval == 0x7FFF){                // ボタンが押されたら
    myDFPlayer.play(random(numfile)+1); //ランダムにファイルを再生 [1, numfile]
  }
  delay(1);
}
