int last = -1;
unsigned long last_time = 0;

void setup()
{
   Serial.begin(115200);
   pinMode(7,INPUT);
   last_time = micros();
  
}

void loop()
{
   int val;

   while(1)
   {
     val = !digitalRead(7);
     if(val != last)break; 
   }

   unsigned long now = micros();
   Serial.print(last);
   Serial.print(",");
   Serial.println(now-last_time);
   Serial.print(val);
   Serial.print(",");
   Serial.println(now-last_time);
   last = val;
   last_time = now;
}
