= トラブルシューティング

== シリアルモニタで文字化けがする

//image[1][1]{
//}
//image[2][2]{
//}
Upload speedが間違っている可能性がある

== プログラムが書き込めない

シリアルポートが間違っているかもしれない

== プログラムを書き込んだが動作に反映されない

//image[3][3]{
//}
プログラムの保存を忘れている
Ctrl+Sで保存してから読み込む

== error: redefinion

//cmd{
c:\Users\donki\Documents\Arduino\helloworld\DHT11.ino: In function 'void setup()':
  DHT11:30:6: error: redefinition of 'void setup()'
   void setup() {
        ^
  c:\Users\donki\Documents\Arduino\helloworld\helloworld.ino:1:6: note: 'void setup()' previously defined here
   void setup() {
        ^
  c:\Users\donki\Documents\Arduino\helloworld\DHT11.ino: In function 'void loop()':
  DHT11:37:6: error: redefinition of 'void loop()'
  void loop() {
        ^
  c:\Users\donki\Documents\Arduino\helloworld\helloworld.ino:5:6: note: 'void loop()' previously defined here
   void loop() {
        ^
  exit status 1 
//}

 * 解決法
 Arduinoコンパイルエラー(redefinition)
 同じフォルダ内にsetup()とloop()が重複している際に出るエラー
 Arduinoはコンパイルをファルダ単位で行うため、このようなエラーが出る