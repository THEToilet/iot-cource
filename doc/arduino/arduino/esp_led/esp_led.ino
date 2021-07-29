void setup()
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  digitalWrite(13, HIGH); // turn the LED on (HIGH is the voltage level)
  Serial.println("high");
  delay(500);             // wait for a second
  digitalWrite(13, LOW);  // turn the LED off by making the voltage LOW
  Serial.println("LOW");
  delay(500);             // wait for a second
}