= トラブルシューティング

== シリアルモニタで文字化けがする
ここでは、筆者がESP32で開発をしていた際に遭遇したエラーとその解決法
を紹介します。

//image[1][文字化けしたシリアルモニタ]{
//}
//image[2][Upload Speedを変更する]{
//}
Upload speedがプログラムの指定と異なっている可能性があります。

== プログラムが書き込めない
シリアルポートが間違っている可能性があります。

== プログラムが反映されない

//image[3][プログラムが保存されていない]{
//}
プログラムの保存を忘れている可能性があります。
Ctrl+Sで保存してから読み込んでください。

== error: redefinion

//cmd{
c:\Users\donki\Documents\Arduino\helloworld\DHT11.ino: In function
'void setup()': DHT11:30:6: error: redefinition of 'void setup()'
 void setup() {
      ^
c:\Users\donki\Documents\Arduino\helloworld\helloworld.ino:1:6:
note: 'void setup()' previously defined here
 void setup() {
      ^
c:\Users\donki\Documents\Arduino\helloworld\DHT11.ino: In function
'void loop()': DHT11:37:6: error: redefinition of 'void loop()'
void loop() {
      ^
c:\Users\donki\Documents\Arduino\helloworld\helloworld.ino:5:6:
note: 'void loop()' previously defined here
 void loop() {
      ^
exit status 1
//}

Arduinoコンパイルエラー(redefinition)
同じフォルダ内にsetup()とloop()が重複している際に出るエラーです。
Arduinoはコンパイルをファルダ単位で行うため、このようなエラーが出ます。
そのため、ファイルを分けてプログラムを作成してください。

== 接続ポートにESP32がない
デバイスマネージャーにESP32の接続ポートが表示されない場合はデバイスドライバをインストールする必要があります。
以下のリンクにアクセスしてください。

//embed[latex]{
\begin{center}
https://jp.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
\end{center}
//}


//image[7][デバイスマネージャー]{
//}
//image[4][ドライバのインストールページ]{
//}
//image[5][インストールしたドライバファイル]{
//}
//image[6][デバイスマネージャーの反映が成功]{
//}

== COMポートが表示されない
デバイスドライバの更新がうまくいっていないか、
USBケーブルが給電専用ケーブルの可能性があります。

== LEDの光り方が弱い
抵抗の大きさが違う可能性あり

== 回路図どうりなのにつかない
ジャンプワイヤが切れている可能性があります。

== Failed to execute script esptool
シリアルモニタを閉じることでこのエラーを解消できた。

== Wi-Fi2.4GHz