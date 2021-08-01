= 環境構築
この章ではESP32にプログラムを書き込む際に必要な環境構築の手順を紹介します。
本誌は、Windows環境を想定しておりMac環境の方は手順が異なる可能性があります。

== ESP32とは
ESP32とはEspressif Systems社が開発したSoC（System on a Chip）シリーズの名前です。
ESP32という名前の使われ方には様々あり今回使用するESP32DevKitC-32E（@<img>{esp32}）は、ESP32をユーザが利用しやすい形にした製品ですが、
通称としてESP32と呼ばれることがあります。そのため、本誌ではESP32DevKitC-32Eも含めてESP32と呼んでいます。
ESP32の特徴としてはBluetoothやWi-Fiモジュールがついている点やマルチコアな点が挙げられます。

//image[esp32][ESP32DevKitC-32E][scale=0.4]{
//}

== ESP32の開発環境

ESP32の開発環境には主に以下の3つが挙げられます。

 * Arduino IDE
 ** Arduino互換ボード用統合開発環境（C/C++）
 * ESP-IDF
 ** ESP32専用の開発環境（C/C++）
 * MicroPython
 ** C言語で作られたPython3と互換性がある言語処理系

今回は利用者が多く、関連情報がネット上に多く見られるArduino IDEを用いて開発を進めていきたいと思います。

== Arduino IDEのインストール

Arduino IDEをインストールするために以下のリンクにアクセスしてください@<br>{}
@<href>{https://www.arduino.cc/en/software}@<br>{}
ダウンロード画面（@<img>{1}）ではご自身のPC環境にあったダウンロードリンクを選択してください。
ここからの手順では、Windows10でのダウンロードを想定しています。

//image[1][ArduinoIDEのダウンロード画面][scale=0.9]{
//}

ダウンロードリンクにアクセスすると、寄付金の金額選択画面に遷移します（@<img>{2}）。
可能であれば寄付もできますが、@<strong>{JUST DOWNLOAD}を選択することで次の画面に遷移します。

//image[2][寄付金の金額選択画面][scale=0.8]{
//}

@<strong>{JUST DOWNLOAD}を選択するとブラウザ内でMicorsoftStoreの画面に遷移します（@<img>{3}）。
@<strong>{入手}を選択すると、ブラウザのポップアップが表示されWindows上でMicrosoftStoreを開く許可を求められるので許可を選択してください。

//image[3][ブラウザで見るMicorosoftStore][scale=0.6]{
//}

Windows上で開かれたMicrosoftStoreです（@<img>{4}）。再度、@<strong>{入手}を選択してください。

//image[4][Windowsで開いたMicrosoftStore][scale=0.6]{
//}

サインインについて尋ねられますが（@<img>{5}）、@<strong>{必要ありません}を選択した場合もダウンロードは開始されます。

//image[5][サインインの確認画面][scale=0.6]{
//}

@<img>{6}ではArduino IDEのダウンロード状況を確認できます。

//image[6][ダウンロードのキュー画面][scale=0.8]{
//}

ダウンロードが完了した後、検索窓にてArduino IDEを検索し開いてください（@<img>{7}）。

//image[7][ArduinoIDEの検索][scale=0.6]{
//}

開いた際、セキュリティについての許可を求められるので（@<img>{8}）@<strong>{アクセスを許可する}を選択してください。

//image[8][セキュリティの確認画面][scale=0.6]{
//}

Arduino IDEが起動すると、デフォルトの画面が表示されます（@<img>{9}）。

//image[9][デフォルトのスケッチ画面][scale=0.7]{
//}

== ESP32用ボードマネージャーのインストール
Arduino IDEにてESP32を使うために必要なボードマネージャーのインストール方法を紹介します。@<br>{}
@<img>{10}はESP32のボードマネージャーを追加するための手順であり、以下のリンクに記載されています。
@<href>{https://github.com/espressif/arduino-esp32/blob/master/docs/arduino-ide/boards_manager.md}@<br>{}
//image[10][ESP32をArduinoIDEで使うための設定][scale=0.8]{
//}
手順に従い以下のリンクをコピーしてください（@<list>{esp32-board-link}）。以下のリンクには、@<img>{11}のような情報が記載されています。
以下のリンクでは改行をしていますが実際は一文のため注意してください。
//list[esp32-board-link][ボードマネージャーのリンク]{
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/⏎
package_esp32_index.json
//}
//image[11][ESP32用のボードマネージャ情報][scale=0.7]{
//}
Arduino IDE側では、ファイル＞環境設定を選択してください（@<img>{12-1}）。
//image[12-1][環境設定を選択][scale=0.8]{
//}
選択した後、環境設定の画面が表示されていることを確認してください（@<img>{13}）。
//image[13][環境設定の画面][scale=0.8]{
//}
次に、先ほどコピーしたリンク（@<list>{esp32-board-link}）を@<strong>{追加ボードマネージャーのURL}の欄にペーストしてください（@<img>{14}）。
//image[14][追加ボードマネージャーのURLに貼り付ける][scale=0.8]{
//}
その後、@<strong>{OK}を選択してください。

次に、ツール＞ボード＞ボードマネージャーを開いてください。

//image[33][ボードマネージャーを開く][scale=0.8]{
//}
開かれたボードマネージャーの検索窓に「ESP32」を入力しインストールをしてください。
//image[34][ESP32用ボードマネージャーのインストール][scale=0.8]{
//}
インストールが完了した後、ツール＞ボード＞ESP32 Arduino＞ESP32 Dev Moduleを選択してください。
//image[17][ボードESP32 Dev Moduleの選択][scale=0.8]{
//}

== Hello ESP32!!
ここで動作確認をするためにプログラミングでは定番のHelloWorldをESP32でやってみましょう。

=== ブレッドボード
これからの作業のためにESP32をブレッドボードにさします。
@<img>{breadboard}のように、esp32をブレッドボード中央あたりに差し込んでください。
ブレッドボードの説明をします。ブレッドボードは電子回路を仮組みする際によく使われます。
ブレッドボードにさした部品は再利用できるため、いろいろな回路を試すことができます。
ブレッドボードの最大の特徴として@<img>{breadboard}のように、回路的につながっている部分とつながっていない部分に分かれているところがあげられます。
最初のうちは、回路的につながっている部分を忘れて、ショートする回路を作ってしまうことがあるので注意してください。
//image[breadboard][ブレッドボード][scale=0.8]{
//}

=== PCとの接続

つぎに、ESP32をPCと接続します。まずmicroUSB Type-Bの差し込み口に（@<img>{usb1}）microUSB Type-B端子を差し込んでください。
//image[usb1][microUSB type-B差し込み口][scale=0.5]{
//}
その後、PCとesp32を接続してください。接続が完了するとesp32上のLEDが光ります（@<img>{pc}）。
//image[pc][PCとの接続][scale=0.5]{
//}

次にデバイスマネージャーを用いて、ESP32がつながっているポート番号を調べます。
デバイスマネージャーを開いてください（@<img>{18}）。
//image[18][デバイスマネーーの検索][scale=0.8]{
//}
ESP32はSilicon Labs CP210x USB to UART Bridgeという名前でCOM3につながっていることがわかります(@<img>{19-1}）。
接続ポートは環境によって異なります。
//image[19-1][ESP32の接続ポートを調べる][scale=0.8]{
//}
先ほど調べた接続ポートを反映するため　ツール＞シリアルポートを選択し変更してください。
//image[29][接続ポートの反映][scale=0.8]{
//}

設定を確認します。ツールを開いてUploadSpeedが115200であることを確認してください。
//image[28][ボードの設定][scale=0.8]{
//}

=== プログラムの記述
HelloWorldを実行するため、新しくファイルを作成します。
ファイル＞新規ファイルを選択してください（@<img>{20}）。
//image[20][新規ファイルの作成][scale=0.8]{
//}
ファイルエクスプローラーが開かれるので、ファイル名にhelloworldと入力して保存してください（@<img>{21}）。
//image[21][新規ファイルの名前決定][scale=0.8]{
//}

つぎに、@<list>{helloworld}を参考にして@<img>{23}のようにプログラムを記述してください。
//list[helloworld][HelloWolrd]{
void setup() {
  Serial.begin(115200);  // シリアル通信をUploadSpeed 115200bpsで開始
}

void loop() {
  Serial.println("Hello,World"); // シリアル通信で"Hello,World"を送信する
  delay(3000); // 3000ms（3秒）停止する
}
//}
//image[23][HelloWorldのプログラムを記述][scale=0.8]{
//}

==== プログラムの説明
ここで、先ほど記述したプログラムの説明をします。
まず、ESP32のプログラムは大枠として

 * setup()
 * loop()

 の二つに分類されます。
 setup()は起動時に一回だけ実行され、loop()はsetup()の実行後、無限に繰り返されます。
そのため、setup()内には初期化などの処理を書き、loop()内にはセンサーの値取得など逐次取得したい内容を書きます。

=== プログラムの書き込み
ここで、esp32にプログラムを書き込みます。矢印を選択し、プログラミングを書き込んでください（@<img>{30}）。
//image[30][ESP32にプログラムを書き込む][scale=0.8]{
//}
矢印を選択するとプログラムの書き込みが開始します。書き込みの様子はコンソール画面にて確認できます（@<img>{31}）。
//image[31][コンソール画面][scale=0.8]{
//}

=== 動作確認
ESP32からのHelloWorldを表示するために、シリアルモニタを開きます。
ツール＞シリアルモニタを選択してください（@<img>{26}）。
//image[26][シリアルモニタの選択][scale=0.8]{
//}
ESP32からHelloWorldが送られてくることを確認できました（@<img>{32}）。
//image[32][helloworldの表示成功][scale=0.8]{
//}

==[column] シリアル通信とは
シリアル通信とは通信線を用いて信号をHIGHとLOWの1/0の組み合わせの連続（シリアル）的に情報を送信するものです。
HelloWorldを受信した際に使用したシリアルモニタはESP32から送られてきた情報を表示したり送信したりする機能です。
またシリアル通信では送信速度と受信速度を一致させる必要があり、これを一秒あたりのビット数（bps）として表します。
プログラムで記載した
//emlist{
Serial.begin(115200);
//}
もesp32とPCとの間の通信速度を115200bpsとして設定しています。
ほかにも
//image[35][UploadSpeedの設定][scale=0.7]{
//}
設定のUploadSpeed（@<img>{35}）や
//image[36][シリアルモニタのbpsの設定][scale=0.7]{
//}
シリアルモニタでの設定（@<img>{36}）も一致する数字にする必要があります。
ちなみにUSBもUniversal Serial Busの略であり、シリアル通信を行っています。
#@#https://qiita.com/hsgucci/items/eee5894e3651d0a8cb75
#@#https://thinkit.co.jp/story/2015/04/15/5791