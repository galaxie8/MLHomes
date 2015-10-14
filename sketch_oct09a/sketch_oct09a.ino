#include <Esplora.h>

int buttonpin = 8;
int LEDpin = 13;
int buttonstate;
void setup() {
  // put your setup code here, to run once:
pinMode(buttonpin,INPUT)
pinMode(LEDpin, OUTPU);
}

void loop() {
  // put your main code here, to run repeatedly:
buttonstate = digitalRead(buttonpin);
if(buttonstate== HIGH)
{
  digitalWrite(LEDpin,HIGH);
  delay(1000);
    digitalWrite(LEDpin,LOW);
delay(100);
}
else
{
}
}
