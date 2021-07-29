//********************************
//オミクジ!プログラム
//********************************
#define BEAT 100   // 音の長さを指定
#define PINNO 8   // 圧電スピーカを接続したピン番号
#include <LiquidCrystal.h>
//lcdを使うヘッダーファイル
LiquidCrystal lcd(12, 11, 10, 6, 5, 4, 3);
//ピン番号を指定してライブラリを初期化する
//LiquidCrystal lcd(rs, rw, enable, d4, d5, d6, d7)
#define input_pin 2
//ボタンで使うピン
int ramdom(int);
void setup()
{
  // LCDの列と行を設定する
  lcd.begin(2,16);
  Serial.begin(9600) ;
  pinMode(input_pin,INPUT);
  randomSeed(analogRead(2));
  //ランダム関数を定義
}
long shake(){
  long x,y,z;
  int i;
  x = y = z = 0;
  x = analogRead(0) ; //x軸
  y = analogRead(1) ; //y軸
  tone(PINNO,262,BEAT);  //ド
  delay(BEAT);
  tone(PINNO,294,BEAT);  //レ
  delay(BEAT);
  lcd.clear();
  lcd.setCursor(3,0);
  //カーソルを１行目3カラム目にセット
  lcd.print("\xb5\xd0\xb8\xbc\xde\xa6\xcc\xaf\xc3\xc8\x21"); //オミクジヲフッテネ
  delay(4000);  
  for(i=0;i<10;i++)
    {
    x = x + analogRead(0);
    y = y + analogRead(1);
    }
  //１０回ループでセンサーの値を足す
  Serial.print("X:") ;
  Serial.println(x) ;
  Serial.print("Y:") ;
  Serial.println(y) ;
  z = x + y;
  Serial.print("z:") ;
  Serial.println(z) ;
  if(z >7000){
    return 6;}
  else if(z == 6000){
    return 0;}
  else return 11;
  delay(30) ;
}

void loop()
{
  int status;
  long abc,cd;
  lcd.clear();
  lcd.setCursor(5,0);
  //カーソルを１行目５カラム目にセット
  lcd.print("\xb5\xd0\xb8\xbc\xde\x21"); //オミクジ！
  delay(2000);
  lcd.clear();
  lcd.setCursor(2,0);
  //カーソルを１行目目2カラム目にセット
  lcd.print("\xce\xde\xc0\xdd\xa6\x3c\xc5\xb6\xde\xb5\xbc\x3e"); //ボタンヲ（ナガオシ）
  lcd.setCursor(6,1);
  //カーソルを２行目６カラム目にセット
  lcd.print("\xbc\xc3\xc8\x21"); //シテネ
  delay(2000);
  status = digitalRead(input_pin);
  if (status == HIGH)
    {
    delay(1000);
    }
  else
    {
    abc = shake();
    lcd.clear();
    cd = random(0,abc);
    //ランダムの値を0からabcにセットする
    Serial.println(cd);
    ramdom(cd); 
    delay(1000);
    
    }
}
int ramdom(int abc){
  tone(PINNO,262,BEAT) ; //ド
  delay(BEAT);
  tone(PINNO,294,BEAT) ; //レ
  delay(BEAT);
  tone(PINNO,330,BEAT) ; //ミ
  delay(BEAT);
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("\xb3\xd7\xc5\xb2\xc1\xad\xb3\xa5\xa5\xa5\xa5"); //ウラナイチュウ・・・
  delay(5000);
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
  switch(abc){
    case 0:
      Serial.println("大吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xc0\xde\xb2\xb7\xc1\x7e\x7e"); //→→ダイキチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xd2\xaf\xc1\xac\xb2\xb2\x21"); //メッチャイイ！
      delay(8000);
      break;
    case 1:
      Serial.println("中吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xc1\xad\xb3\xb7\xc1\x7e\x7e");
      //→→チュウキチ→→
      lcd.setCursor(1,1);
      // カーソルを2行目1カラム目にセット
      lcd.print("\xb2\xb2\x21");
      delay(8000);
      break;
    case 2:
      Serial.println("小吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xbc\xae\xb3\xb7\xc1\x7e\x7e"); //→→ショウキチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xcf\xb1\xcf\xb1\xb2\xb2\x21");  //
      delay(8000);
      break;
    case 3:
      Serial.println("吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xb7\xc1\x7e\x7e"); //→→キチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xc1\xae\xaf\xc4\xb2\xb2\x21"); //     
      delay(8000);
      break;
    case 4:
      Serial.println("半吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xca\xdd\xb7\xc1\x7e\x7e"); //→→ハンキチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xca\xdd\xcc\xde\xdd\xb2\xb2\x21");      
      delay(8000);
      break;
    case 5:
      Serial.println("末吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xbd\xb4\xb7\xc1\x7e\x7e"); //→→スエキチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xb1\xc4\xb6\xd7\xb2\xb2\x21"); //     
      delay(8000);
      break;
    case 6:
      Serial.println("末小吉");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xbd\xb4\xbc\xae\xb3\xb7\xc1\x7e\x7e"); //→→スエショウキチ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xb1\xc4\xb6\xd7\xc1\xae\xaf\xc4\xb2\xb2\x21"); //    
      delay(8000);
      break;
    case 7:
      Serial.println("凶");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xb7\xae\xb3\x7e\x7e"); //→→キョウ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xdc\xd9\xb2"); //         
      delay(8000);
      break;
    case 8:
      Serial.println("小凶");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xbc\xae\xb3\xb7\xae\xb3\x7e\x7e"); //→→ショウキョウ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xbd\xba\xbc\xdc\xd9\xb2"); //     
      delay(8000);
      break;
    case 9:
      Serial.println("半凶");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xca\xdd\xb7\xae\xb3\x7e\x7e"); //→→ハンキョウ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xc1\xae\xaf\xc4\xdc\xd9\xb2");  //     
      delay(8000);
      break;
    case 10:
      Serial.println("末凶");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xbd\xb4\xb7\xae\xb3\x7e\x7e"); //→→スエキョウ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xbd\xba\xde\xb8\xdc\xd9\xb2"); //      
      delay(8000);
      break;
    case 11:
      Serial.println("大凶");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("\x7e\x7e\xc0\xde\xb7\xae\xb3\x7e\x7e"); //→→ダイキョウ→→
      lcd.setCursor(1,1);       // カーソルを2行目1カラム目にセット
      lcd.print("\xd2\xaf\xc1\xac\xdc\xd9\xb2"); //
      delay(8000);
      break;
          }

}
