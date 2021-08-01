= 電子部品を使ってみよう

== 部品説明
ESP32で電子部品をつかった回路を組む前に、それぞれの部品の概要を紹介します。

=== LED
LED（発光ダイオード）は決まった方向に電圧を加えることで、発光する半導体素子です。
LEDには極性があり、以下の二つに分けられます。画像(@<img>{led})

 * アノード
 ** 端子の長いほうをアノードと呼び電源の＋に接続する
 * カソード
 ** 端子の短いほうをカソードと呼ぶGND（マイナス）に接続

極性を逆に繋ぐと光らないので注意してください。

//image[led][LEDの端子の違い][scale=0.6]{
//}
　
極性のほかにも点灯のために必要な情報があります。
代表的なものに以下の二つの要素があげられます。

 * 順電圧（Vf）
 ** LEDは発光するため一定値以上の電圧をかける必要があります。これを順電圧（Vf）と呼びます。
 * 順電流（lf）
 ** LEDは流す電流の大きさによって明るさが変わりますが、電流を流しすぎると壊れてしまいます。そこで順電圧（Lf）を用いて適切な電流値を表します。

==== 抵抗値の求め方
先述の二つを用いてLEDとesp32の間に接続する抵抗値の選択をします。

抵抗にかかる電圧を求める、LEDかかる電圧は「順電圧」の値を用いる
LEDに流れる電流が変化してもかかる電圧に大きな変化がないため
抵抗にかかる電圧は電源電圧からLEDの順電圧を引いた値
3.3v - 2v
LEDに流す電流値を決める
通常はLEDの順電流の値を利用する
しかしラズパイではGPIOに流れる電流が16ｍAまでと決まっている
そのため10mAをながすとする
オームの法則から抵抗値を決める
1.3/0.01 = 130オームとなる
しかし130オームの抵抗を新しく用意するのはめんどいので
100オームの抵抗を使う
1.3/100 = 13mAとなり
ラズパイの許容範囲なのでおｋ

=== ジャンプワイヤ
主にブレッドボード上で、電子回路を仮組する際に使われるものがジャンプワイヤです。
ジャンプワイヤには、いくつかの種類があり主に以下の二つがあります。

 * オス・オス
 ** 両端子とも基盤にさして使う（@<img>{zyanpu}）。
 * オス・メス
 ** 片方が端子を差し込めるようになっている（@<img>{zyanpu_mesu}）。

//image[zyanpu][ジャンプワイヤ オス・オス][scale=0.4]{
//}
//image[zyanpu_mesu][ジャンプワイヤ オス・メス][scale=0.4]{
//}

=== 抵抗
電子回路上を流れる電流を調整するために使われるのが抵抗であり（@<img>{regi1}）、抵抗値によって様々なものがあります。
これを見分けるための規格があり以下の表によって決められています（@<table>{regi}）。
//image[regi1][330Ω抵抗][scale=0.8]{
//}
許容差とは抵抗のばらつき度を表しています。

//table[regi][抵抗値]{
色	有効数字	乗数	許容差[%]
------------------
@<icon>{black}黒	0	@<m>{10^0（1）}	.
@<icon>{brown}茶		1	@<m>{10^1（10）}	±1
@<icon>{red}赤	2	@<m>{10^2（100）}	±2
@<icon>{orange}オレンジ	3	@<m>{10^3（1000）}	±0.05
@<icon>{yellow}黄	4	@<m>{10^4（10000）}	.
@<icon>{green}緑	5	@<m>{10^5（100000）}	±0.5
@<icon>{blue}青	6	@<m>{10^6（1000000）}	±0.25
@<icon>{purple}紫	7	@<m>{10^7（10000000）}	±0.1
@<icon>{gray}灰	8	@<m>{10^8（100000000）}	.
@<icon>{white}白	9	@<m>{10^9（1000000000）}	.
@<icon>{gold}金	.	10^(-1)（0.1）	±5
@<icon>{silver}銀	.	10^(-2)（0.01）	±10
@<icon>{none}無色	.	.	±20
//}


//image[colorcode][カラーコード][scale=0.8]{
//}

=== タクトスイッチ

//image[tac1][抵抗１][scale=0.6]{
//}
//image[switch_con][switch_con][scale=0.6]{
//}

==== プルアップとプルダウン
Vdd
電気の＋を表す表記に使われることがある
VはVoltageから
スイッチを利用すれば2つの値を切り替えられる回路を作れます。
しかし，スイッチがオフの場合では，出力する端子が解放状態（何も接続されてない状態）になる
この場合周囲の雑音を拾ってしまい，値が安定しない状態になる
そこで，プルダウンやプルアップを使って安定させる
方法としてはGNDやVdd（電源）に接続しておく方法
こうしておくことでスイッチがオフ状態のとき，出力端子に接続されている抵抗を介して値を安定させる
スイッチOFF時に0vに安定させる方法をプルダウン
電圧がかかった状態に安定させる方法をプルアップと呼ぶ
//image[pullupdown][pullupdown]{
//}

== Lチカしよう！
Lチカとは、ハードにおけるHelloWolrdです。
LEDをチカチカさせるだけですが、実際にLEDを光らせることができるとわくわくします。

=== プログラムでLチカ
Lチカですが、ESP32を使用することで、容易に実現できます。
ArduinoIDEから新規作成を選択し、新たなファイルを作成して
以下のプログラムを貼り付けてください。

//image[led2][led2]{
//}
//list[Ltic][Ltic]{
void setup() {
  pinMode(13, OUTPUT);
}
void loop() {
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
}
//}

=== タクトスイッチでLチカ
せっかくなので、スイッチを使用して、LEDを光らせましょう
同様に以下の画像を参考に電子回路を組み、プログラムを参考にして、
ESP32に書き込んでください。
//image[switch2][switch2]{
//}
//list[switch][switch]{
void setup()
{
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop()
{
  if (digitalRead(2) == LOW)
  {
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    Serial.println("ON!");
  }
  if (digitalRead(2) == HIGH)
  {
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    Serial.println("OFF!");
  }
}
//}

==[column] コラム: チャタリング
スイッチは金属板の接触によって、電流を通したり、通さなかったりしますが、
これを行う際、複数回のオンオフが発生してしまいます。この対策としては、
プログラム側で、delayをはさむことが挙げられます。
//emlist{
if (digitalRead(2) == LOW)
{
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);
  Serial.println("ON!")
}
//}

== 応用問題: 状態遷移
二つのLEDとスイッチを使用して、
二つのLEDの状態を以下のように変更してください
//image[ltica][ouyou][scale=0.6]{
//}

2019年度組み込み制作講座より引用

注意　ループの中で、無限ループはできない

//image[switch3][switch3]{
//}

//list[ltica_tica][状態遷移Lチカ]{
void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}
void loop() {
  int state = 0;
  bool is_tica = false;
  if (digitalRead(2) == LOW)
  {
    delay(100);
    Serial.println("ON!");
    state++;
    if (state == 5) {
      state = 0;
      is_tica = false;
    }
    switch (state) {
      case 0:
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
        break;
      case 1:
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        break;
      case 2:
        digitalWrite(12, LOW);
        digitalWrite(13, HIGH);
        break;
      case 3:
        digitalWrite(12, HIGH);
        digitalWrite(13, HIGH);
        break;
      case 4:
        is_tica = true;
        break;
      default:
        break;
    }
    delay(2000);
  }
  if (digitalRead(2) == HIGH) {
    delay(100);
    Serial.println("OFF!");
  }
  if (is_tica) {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(12, HIGH);
    delay(100);
  }
}
//}
