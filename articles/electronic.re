= 電子部品を使ってみよう


== 部品説明
ここでは、サンプルを作成するに際に使用する電子部品の説明を行います。

=== LED

 * アノード 

極性は端子の長いほうをアノードと呼び電源の＋に接続する

 * カソード

端子の短いほうをカソードと呼ぶカソード側は中の金属板が大きい
　　
 * 点灯のために必要な情報
 ** 順電圧（vf）
 ** 順電流（lf）
　　
ラズパイで利用する場合は順電圧が2v程度，順電流が20mA程度

=== ジャンプワイヤ

オスメス

=== 抵抗

抵抗見分け方

=== タクトスイッチ

 * プルアップとプルダウン
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
Lチカとは、ハードにおける、プログラムのHelloWolrdです。
LEDをチカチカさせるだけですが、実際にLEDを光らせることができると
わくわくします。

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
==[/column]

== 応用問題: 状態遷移
二つのLEDとスイッチを使用して、
二つのLEDの状態を以下のように変更してください
//image[ltica][ouyou][scale=0.6]{
//}

2019年度組み込み制作講座より引用