/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
/*
 * Copyright: DFRobot
 * name:  DFPlayer_Mini_Mp3 sample code
 * Author:  lisper 
 * Date:  2014-05-30
 * Description: sample code for DFPlayer Mini, this code is test on Uno
 *   note: mp3 file must put into mp3 folder in your tf card
 */
 /*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
 
#include <IRremote.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#define SW  6
#define RX_PIN 10
#define TX_PIN 11

SoftwareSerial mySoftwareSerial(RX_PIN, TX_PIN); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

IRsend irsend;

boolean button = 0;

const int LED_PIN = 2;
const int LED_PI = 4;
const int LED_P = 5;
int i = 0;

 
void setup() {
  mySoftwareSerial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
  
  Serial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  myDFPlayer.volume(30);  // 音量の設定(0～30)
  pinMode( LED_PIN, OUTPUT );
  pinMode( LED_PI, OUTPUT );
  pinMode( LED_P, OUTPUT );
  
}
 
void loop() {

  if (!digitalRead(SW))
  {
    button = !button;
    irsend.sendSony(0xa90, 12); // Sony TV power code
    myDFPlayer.play(1); //play 0001.mp3
    i++;
    delay(40);
     
    
  }

  if(i==1)
  {
    digitalWrite( LED_PIN, HIGH );
  }

  else if(i==2)
  {
      digitalWrite( LED_PI, HIGH );
  }
  
  else if(i==3)
  {
      digitalWrite( LED_P, HIGH );
  }
  delay(100);
}
