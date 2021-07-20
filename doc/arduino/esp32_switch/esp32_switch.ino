void setup()
{
  Serial.begin(115200);

  pinMode(2, INPUT_PULLUP); //GPIO32を入力に
}

void loop()
{
  if (digitalRead(2) == LOW)
  { //32ピンのタクトスイッチが押された時
    delay(200);
    Serial.println("ON!");
  }
  if (digitalRead(2) == HIGH)
  { //33ピンのタクトスイッチが押された時
    delay(200);
    Serial.println("OFF!");
  }
}