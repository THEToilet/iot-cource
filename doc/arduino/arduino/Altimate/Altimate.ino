//https://github.com/Neco777/Arduino-IRremote/blob/master/examples/IRrecvMulti/IRrecvMulti.ino

#include "IRremote.h"
#include "CppList.h"

bool _initialized = false;

int rcv_count;
IRrecv **all_rcv;

void setup() {
  if (_initialized) return;
  
  Serial.begin(9600);
  
  rcv_count = 5;
  all_rcv = (IRrecv **)malloc(rcv_count*sizeof(int));
  all_rcv[0] = new IRrecv(3);
  all_rcv[1] = new IRrecv(4);
  all_rcv[2] = new IRrecv(7);
  all_rcv[3] = new IRrecv(8);
  all_rcv[4] = new IRrecv(11);
  
  for (int i=0; i<rcv_count; i++){
    all_rcv[i]->enableIRIn(); //構造体配列のポインタ表現?
  }
  
  _initialized = true;
}

void loop() {
  for (int i=0; i<rcv_count; i++){
    decode_results results;
    if (all_rcv[i]->decode(&results)) {
      Serial.print("Rcv_");
      Serial.print(i);
      Serial.print("\n");
      all_rcv[i]->resume();
    }
  }
}
