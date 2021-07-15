= 環境構築

この章ではESP32を利用するために必要な環境構築手順を説明します。

Windows環境を想定しているので、Mac環境の方は少しやり方が違うかもしれません。

== ESP32とは
ESP32ってなに？？？

== Arduino IDEのインストール
//image[1][1]{
//}
//image[2][2]{
//}
//image[3][3]{
//}
//image[4][4]{
//}
//image[5][5]{
//}
//image[6][6]{
//}
//image[7][7]{
//}
//image[8][8]{
//}
//image[9][9]{
//}
//image[10][10]{
//}
//image[11][11]{
//}
//image[12][12]{
//}
//image[13][13]{
//}

== ESP32用ボードマネージャーのインストール

== 動作確認
ここで動作確認をするために定番のHelloWorldを行いましょう 

=== ブレッドボード
まずESP32をブレッドボードにさしましょう

//image[14][14]{
//}
//image[15][15]{
//}
//image[16][17]{
//}
//image[18][18]{
//}
//image[19][19]{
//}
//image[20][20]{
//}
//image[21][21]{
//}
//image[22][22]{
//}
//image[23][23]{
//}
//image[24][24]{
//}
//image[25][25]{
//}
//image[26][26]{
//}
//image[27][27]{
//}
//list[helloworld][最初のプログラム]{
void setup() { 
  Serial.begin(115200); 
} 

void loop() { 
  Serial.println("Hello,World"); 
  delay(3000); 
}
//} 