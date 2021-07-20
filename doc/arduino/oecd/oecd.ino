#include <Wire.h>
#include <string>
#include "SSD1306.h" //ディスプレイ用ライブラリを読み込み
using namespace std;

SSD1306 display(0x3c, 21, 22); //SSD1306インスタンスの作成（I2Cアドレス,SDA,SCL）

int i = 0;
void setup()
{

  display.init();                          //ディスプレイを初期化
  display.setFont(ArialMT_Plain_16);       //フォントを設定
  display.drawString(0, 0, "Hello World"); //(0,0)の位置にHello Worldを表示
  display.display();                       //指定された情報を描画
}

void loop()
{
  i++;
  display.setPixel(i, i + 10);
  if (i == 100)
  {
    i = 0;
  }
  display.display();
}
