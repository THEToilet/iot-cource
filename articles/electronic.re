= 電子部品を使ってみよう

== 部品説明
ESP32で電子部品を用いた回路を組む前に、それぞれの部品の概要を紹介します。

=== LED
LED（発光ダイオード）は決まった方向に電圧を加えることで、発光する半導体素子です。
LEDには極性があり、以下の二つに分けられます(@<img>{led})。

 * アノード
 ** 端子の長いほうをアノードと呼び電源の＋に接続する
 * カソード
 ** 端子の短いほうをカソードと呼ぶGND（マイナス）に接続

極性を逆に繋ぐと光らないので注意してください。

//image[led][LEDの端子の違い][scale=0.6]{
//}
　
極性のほかにも点灯のために必要な情報があります。
代表的なものに以下の二つがあります。

 * 順電圧（Vf）
 ** LEDは発光するため一定値以上の電圧をかける必要があります。これを順電圧（Vf）と呼びます。
 * 順電流（lf）
 ** LEDは流す電流の大きさによって明るさが変わりますが、電流を流しすぎると壊れてしまいます。そこで順電流（lf）を用いて適切な電流値を表します。

==== 抵抗値の求め方
先述の二つを用いてLEDとESP32の間に接続する抵抗値の選択をします。
今回使うLEDは

順電圧（Vf）: 2.1V 順電流（lf）: 20mAです。

まずLEDにかかる抵抗にかかる電圧を求めます。
GPIOから出力される電圧は3.3V、LEDにかかる電圧は順電圧を用いて2.1Vとします。
そこからLEDにかかる電圧を求めると

@<m>{3.3V - 2.1V = 1.2V}

より1.2Vが抵抗にかかる電圧だと分かりました。
次に抵抗にかかる電流値を求めます。ESP32のGPIOにかけてもいい最大電流値は20mA（おそらく）なので
オームの法則を用いて抵抗値を求めると

@<m>{1.2V / 0.002A = 600Ω}

600Ωが必要ということが分かりました。しかし、今回は100Ωの抵抗を用意したので

@<m>{1.2V / 100Ω = 0.012A（12mA）}

より100Ωの抵抗を使っても流れる電流は12mAでありESP32の許容範囲内です。

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
電子回路上を流れる電流を調整するために使われるのが抵抗であり（@<img>{regi330}）、抵抗値によって様々なものがあります。
これを見分けるための規格があり以下の表のように決められています（@<table>{regi}）。
//image[regi330][330Ω抵抗][scale=0.5]{
//}
許容差とは抵抗のばらつき度を表しています。

//table[regi][抵抗のカラーコード]{
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

実際に抵抗の値をカラーコードから読み取ってみましょう。
@<img>{colorcode}を見てください。今回は4本線の場合を考えます。
まず左側の二つの線の色を見るとどちらもオレンジなので@<table>{regi}から33ということが分かります。
次に右側の二つ線の色を見ると茶色と金色なので乗数が100許容差が±5%ということが分かります。
これらのことから、この抵抗は抵抗値330Ωで許容差±5%だということが分かりました。
//image[colorcode][抵抗値の読み取り][scale=0.7]{
//}

=== タクトスイッチ
タクトスイッチはスイッチを押すことで、電流の止めたり流したりできる部品です。
主にプログラムのリセットやメッセージ送信スイッチなどに使われます。

//image[tactoswitch][タクトスイッチ][scale=0.6]{
//}
タクトスイッチには通常時繋がっている部分と繋がっていない部分があります。
@<img>{switch_con}を見てもらうと分かるように黄色の線の部分は通常時繋がっていて、
オレンジ色の線の部分はタクトスイッチを押すと繋がります。
//image[switch_con][タクトスイッチの特徴][scale=0.6]{
//}

==== プルアップとプルダウン
タクトスイッチなどのスイッチを用いることで、電流を流したり止めたりすることができます。
しかし、出力する端子に何もつながっていない状況（@<img>{tswitch}）では不安定になってしまいノイズなどの影響を受けやすくなってしまいます。
そこで、これを解決するために以下の二つの方法を用います（@<img>{pullupdown}）。
//image[tswitch][オフ状態のスイッチ]{
//}

まず前提として、Vddは電気の＋側をGNDは電気の－側を表しています。またOUT PUTはESP32でいうところの
入出力が可能なピンであるGPIO（General Purpose Input/Output: 汎用入出力）をさしています。

まず@<img>{pullupdown}の右側に記載してあるPULL UPは常にOUT PUTに電圧をかけ、スイッチが押された際にはOUT PUTへの電圧が0になる回路です。
これによりノイズの影響を少なくしています。

つぎに@<img>{pullupdown}の左側に記載してあるPULL DOWNはOUT PUTをGNDにつないでおくことでかかる電圧を0に維持しています。スイッチが押された
際には電圧がOUT PUTにかかります。これによりノイズの影響を少なくしています。

これら二つの方法を用いることで安定した回路を組むことができます。
//image[pullupdown][PULL UPとPULL DOWN][scale=0.8]{
//}

== Lチカしよう！
Lチカとは、ハードにおけるHelloWolrdです。
LEDをチカチカ点滅させてみましょう！！

=== プログラムでLチカ
Lチカですが、ESP32を使用することで、容易に実現できます。
ArduinoIDEから新規作成を選択し、新たなファイルを作成して
以下のプログラムを貼り付けてください。
回路図ではブレッドボードを二枚用いていますが、今回使用するブレッドボードでは一枚の中に収まるようになっています。

//image[led2][led2]{
//}
//list[Ltic][Ltic]{
void setup() {
  pinMode(13, OUTPUT);  // GPIO13を出力端子として用いる
}
void loop() {
  digitalWrite(13, HIGH);  // GPIO13に電流を流しLEDを光らせる
  delay(100);  // 0.1s停止
  digitalWrite(13, LOW);  // GPIO13の電流を止める
  delay(100);  // 0.1s停止
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
  Serial.begin(115200);  // シリアル通信を115200bpsで開始する
  pinMode(2, INPUT_PULLUP);  // GPIO2を用いるまた、ESP32の内部でPULL UPをする
  pinMode(13, OUTPUT);  // GPIO13を出力端子として用いる
}

void loop()
{
  if (digitalRead(2) == LOW)  // PULL UPを用いているので電圧が低いと、
                              // スイッチが押されていると判定する
  {
    delay(100);  // チャタリング防止のため0.1s停止
    digitalWrite(13, HIGH);  // GPIO13に電流を流しLEDを光らせる
    Serial.println("ON!");
  }
  if (digitalRead(2) == HIGH)  // スイッチを押していない場合
  {
    delay(100);  // チャタリング防止のため0.1s停止
    digitalWrite(13, LOW);  // GPIO13の電流を止める
    Serial.println("OFF!");
  }
}
//}

==[column] チャタリング
スイッチを押した際、内部の金属板の接触によって電流が流れます。
しかし、人間がスイッチを押すときには一回だけ押したつもりでも内部的には金属板が何回も
接触し複数回のONOFFが発生する可能性があります。
そのためプログラム側での対策として、delayを何秒か挟むことで複数回のONOFFを防ぐことができます（@<list>{chat}）。
//list[chat][チャタリング防止のプログラム]{
if (digitalRead(2) == LOW)  // PULL UPを用いているので電圧が低いと、スイッチが押されていると判定する
{
  delay(100);  // チャタリング防止のため0.1s停止
  Serial.println("ON!");
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
int state = 0;
bool is_tica = false;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(2, INPUT_PULLUP);
}
void loop() {
  if (digitalRead(2) == LOW)
  {
    delay(100);
    Serial.println("ON!");
    state = state + 1;
    Serial.println(state);
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
    delay(200);
  }
  if (is_tica) {
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);
    delay(100);
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);
    delay(100);
  }
}
//}
