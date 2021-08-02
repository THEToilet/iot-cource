= トラブルシューティング

== シリアルモニタで文字化けがする

//image[1][1]{
//}
//image[2][2]{
//}
Upload speedが間違っている可能性がある

== プログラムが書き込めない

シリアルポートが間違っているかもしれない

== プログラムが反映されない

//image[3][3]{
//}
プログラムの保存を忘れている
Ctrl+Sで保存してから読み込む

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

 * 解決法
 Arduinoコンパイルエラー(redefinition)
 同じフォルダ内にsetup()とloop()が重複している際に出るエラー
 Arduinoはコンパイルをファルダ単位で行うため、このようなエラーが出る

== 接続ポートにESP32が反映されない
デバイスマネージャーにESP32の接続ポートが表示されない場合はデバイスドライバをインストールする必要があります。
以下のリンクにアクセスしてください。
@<href>{https://jp.silabs.com/developers/usb-to-uart-bridge-vcp-drivers}

//image[4][3]{
//}
//image[5][3]{
//}
//image[6][3]{
//}
//image[7][3]{
//}