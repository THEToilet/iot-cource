= 環境構築
この章ではESP32を利用するために必要な環境構築手順を紹介します。
本誌は、Windows環境を想定しているので、Mac環境の方は少々が違う点がある可能性があります。

== ESP32とは
ESP32とは
Espressif Systems社が開発したSoC(System on a Chip)シリーズの名前です。
ESP32という名前の使われ方には様々あり、今回使用するESP32DevKitCはESP32をユーザが利用しやすい形にした製品ですが、
通称としてESP32と呼ばれることもあります。そこで、本誌ではESP32DevKitCも含めてESP32と呼んでいます。

== ESP32の開発環境

ESP32の開発環境としては主に以下の3つがあげられます。

 * Arduino IDE
 ** Arduino用IDE 
 * ESP-IDF
 ** ESP32純正IDE
 * MicroPython
 ** Pythonで書ける

今回は利用者が多く、関連情報がネット上に多く見られるArduino IDEを用いて開発を進めていきたいと思います。

== Arduino IDEのインストール

Arduino IDEをインストールするために以下のリンクにアクセスしてください@<br>{}
@<href>{https://www.arduino.cc/en/software}@<br>{}
ダウンロード画面（@<img>{1}）ではご自身のPC環境にあったダウンロードリンクを選択してください。
ここからの手順では、Windows10でのダウンロードを想定しています。

//image[1][ArduinoIDEのダウンロード画面][scale=0.8]{
//}

ダウンロードリンクにアクセスすると、寄付金の金額選択画面に遷移します（@<img>{2}）。
可能であれば寄付もできますが、@<strong>{JUST DOWNLOD}を選択することで次の画面に遷移します。

//image[2][寄付金の金額選択画面][scale=0.8]{
//}

@<strong>{JUST DOWNLOD}を選択するとブラウザ内でMicorsoftStoreの画面に遷移します（@<img>{3}）。
つぎは@<strong>{入手}を選択すると、ブラウザのポップアップにでWindows側でMicrosoftStoreを開く許可を求められるので許可をしてください。

//image[3][ブラウザで見るMicorosoftStore][scale=0.8]{
unko
//}

Windows上のMicrosoftStoreです（@<img>{4}）。再度、@<strong>{入手}を選択してください。

//image[4][Windowsで開いたMicrosoftStore][scale=0.8]{
//}

サインインについて尋ねられますが（@<img>{5}）、@<strong>{必要ありません}を選択した場合もダウンロードは開始されます。

//image[5][サインインの確認画面][scale=0.8]{
//}

@<img>{6}ではArduino IDEのダウンロード状況を確認できます。

//image[6][ダウンロードのキュー画面][scale=0.8]{
//}

ダウンロードが完了した後、検索窓にてArduino IDEを検索し開いてください（@<img>{7}）。

//image[7][ArduinoIDEの検索][scale=0.8]{
//}

この際、セキュリティについての許可を求められるので（@<img>{8}）@<strong>{アクセスを許可する}を選択すると、ブラウザのポップアップにでWindows側でMicrosoftStoreを開く許可を求められるので許可をしてください。

//image[8][セキュリティの確認画面][scale=0.8]{
//}

Arduino IDEが起動すると、デフォルトの画面が表示されます（@<img>{9}）。

//image[9][デフォルトのスケッチ画面][scale=0.8]{
//}

== ESP32用ボードマネージャーのインストール
Arduino IDEにてESP32を使うために必要なボードマネージャーのインストールの流れを紹介します。@<br>{}
@<img>{10}はESP32のボードマネージャーを追加するための手順であり、以下のリンクに記載されています。
@<href>{https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md}@<br>{}
//image[10][ESP32をArduinoIDEで使うための設定][scale=0.8]{
//}
手順に従い以下のリンクをコピーしてください。以下のリンクには、@<img>{11}のような情報が記載されています。
//list[esp32-board-link][ボードマネージャーのリンク]{
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
//}
//image[11][ESP32用のボードマネージャ情報][scale=0.8]{
//}
Arduino IDE側では、ファイル＞環境設定を選択してください（@<img>{12}）。
//image[12][環境設定を選択][scale=0.8]{
//}
環境設定の画面が表示されていることを確認してください（@<img>{13}）。
//image[13][環境設定の画面][scale=0.8]{
//}
次に先ほどコピーした@<list>{esp32-board-link}を@<strong>{追加ボードマネージャーのURL}の欄にペーストしてください（@<img>{14}）。
//image[14][追加ボードマネージャーのURLに貼り付ける][scale=0.8]{
//}
その後、@<strong>{OK}を選択してください。

== ESP32用ライブラリのインストール
//image[15][ライブラリの管理の選択][scale=0.8]{
//}
//image[16][ESP32用ライブラリのインストール][scale=0.8]{
//}


== Hello ESP32!!
ここで動作確認をするためにプログラミングでは定番のHello WorldをESP32でもやってみましょう。

=== プログラムの記述

//image[20][新規ファイルの作成][scale=0.8]{
//}
//image[21][新規ファイルの名前決定][scale=0.8]{
//}
//image[22][新規ファイル作成完了画面][scale=0.8]{
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
//image[23][helloworldのプログラムを記述][scale=0.8]{
//}

==== プログラムの説明

 * setup()

 * loop()
 

=== ブレッドボード
これからの動作確認のためにESP32をブレッドボードにさしましょう。
そこで、まずブレッドボードの説明をします。

//image[breadboard][ブレッドボード][scale=0.8]{
//}

=== PCとの接続
//image[18][デバイスマネージャーの検索][scale=0.8]{
//}
//image[19][ESP32の接続ポートを調べる][scale=0.8]{
//}

=== プログラムの書き込み
//image[24][ESP32にプログラムを書き込む][scale=0.8]{
//}
//image[25][コンソール画面][scale=0.8]{
//}

=== 動作確認
//image[26][シリアルモニタの選択][scale=0.8]{
//}
//image[27][helloworldの表示成功][scale=0.8]{
//}

==[column] シリアル通信とは
ArduinoIDEはシリアルモニタを備えていて、Arduinoとコミュニケーションすることができます。
==[/column]