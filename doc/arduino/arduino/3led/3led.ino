const int LED_PIN = 3;
const int LED_PI = 4;
const int LED_P = 5;

void setup() {
  pinMode( LED_PIN, OUTPUT );
  pinMode( LED_PI, OUTPUT );
  pinMode( LED_P, OUTPUT );
}

void loop() {
  digitalWrite( LED_PIN, HIGH );
  delay( 1000 );
  digitalWrite( LED_PIN, LOW );
  delay( 1000 );
  digitalWrite( LED_PI, HIGH );
  delay( 1000 );
  digitalWrite( LED_PI, LOW );
  delay( 1000 );
  digitalWrite( LED_P, HIGH );
  delay( 1000 );
  digitalWrite( LED_P, LOW );
  delay( 1000 );
}
