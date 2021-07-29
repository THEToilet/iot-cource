#include <IRremote.h>
 
IRrecv irrecv(11);
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
}
 
void loop() {
  if (irrecv.decode(&results)) {
    if (results.decode_type == SONY) Serial.print("It's SONY!  ");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
