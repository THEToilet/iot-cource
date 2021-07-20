/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>
#define SW  4


IRsend irsend;

boolean button = 0;
 
void setup() {
  pinMode(SW, INPUT_PULLUP);
  Serial.begin(9600);
}
 
void loop() {

  if (!digitalRead(SW))
  {
    button = !button;
    //Sonyのリモコン情報送信
    irsend.sendSony(0xa90, 12);
  }
  delay(100);
}
