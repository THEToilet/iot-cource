= 環境構築

この章ではESP32を利用するために必要な環境構築手順を説明します。

Windows環境を想定しているので、Mac環境の方は少しやり方が違うかもしれません。

== ESP32とは

ESP32ってなに？？？

Espressif Systems社が開発したSoC(System on a Chip)シリーズの名前
環境開発環境として

 * Arduino IDE 
 * ESP-IDF
 * MicroPython

などがありますが、今回はArduino IDEを用いて開発を進めていきたいと思います。

== Arduino IDEのインストール
//image[1][ArduinoIDEのダウンロード画面]{
//}
//image[2][寄付金の金額選択画面]{
//}
//image[3][ブラウザで見るMicorosoftStore]{
//}
//image[4][Windowsで開いたMicrosoftStore]{
//}
//image[5][サインインの確認画面]{
//}
//image[6][ダウンロードのキュー画面]{
//}
//image[7][ArduinoIDEの検索]{
//}
//image[8][セキュリティの確認画面]{
//}
//image[9][デフォルトのスケッチ画面]{
//}
//image[10][ESP32をArduinoIDEで使うための設定]{
//}
//image[11][ESP32用のボードマネージャ情報]{
//}
//image[12][環境設定を選択]{
//}
//image[13][環境設定の画面]{
//}
//image[14][追加ボードマネージャーのURLに貼り付ける]{
//}

@<href>{https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md}

== ESP32用ボードマネージャーのインストール

@<href>{https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json}

== 動作確認

ここで動作確認をするために定番のHelloWorldを行いましょう 

=== ブレッドボード
まずESP32をブレッドボードにさしましょう

//image[15][ライブラリの管理の選択]{
//}
//image[16][ESP32用ライブラリのインストール]{
//}
//image[18][デバイスマネージャーの検索]{
//}
//image[19][ESP32の接続ポートを調べる]{
//}
//image[20][新規ファイルの作成]{
//}
//image[21][新規ファイルの名前決定]{
//}
//image[22][新規ファイル作成完了画面]{
//}
//image[23][helloworldのプログラムを記述]{
//}
//image[24][ESP32にプログラムを書き込む]{
//}
//image[25][コンソール画面]{
//}
//image[26][シリアルモニタの選択]{
//}
//image[27][helloworldの表示成功]{
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

===[column] シリアル通信とは
ArduinoIDEはシリアルモニタを備えていて、Arduinoとコミュニケーションすることができます。