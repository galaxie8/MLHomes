#include <dht.h>

dht DHT;
int temp;
int Ftemp;
int humid;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
DHT.read11(2);
 temp = DHT.temperature;
 humid = DHT.humidity;
 Ftemp = temp * 1.8;
Ftemp += 32;
Serial.print("Temp: ");
Serial.println(Ftemp);
Serial.print("humidity: ");
Serial.println(humid);
Serial.println();
delay(1000);
}
