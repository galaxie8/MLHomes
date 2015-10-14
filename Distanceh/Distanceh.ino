/*-----( Import needed libraries )-----*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
/*-----( Declare Constants and Pin Numbers )-----*/
#define CE_PIN   9
#define CSN_PIN 10

// NOTE: the "LL" at the end of the constant is "LongLong" type
const uint64_t Tpipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
const uint64_t Rpipe = 0xF0F0F0F0E1LL;  // Define the receive pipe
const uint64_t Tpipe1 = 0xE7E7F0F0E1LL; // Define the transmit pipe
const uint64_t Rpipe1 = 0xF6F6F0F0E1LL;  // Define the receive pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio
/*-----( Declare Variables )-----*/
//int RDistanceArray[2];  // 2 element array holding data readings
int TDistanceArray[3];

boolean Started = true;
long Time;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  delay(1000);
  Serial.println("Startig hackathon");
  radio.begin();
radio.setRetries(0,15);
}

void loop() {
  // put your main code here, to run repeatedly:
TDistanceArray[0] = 011;
TDistanceArray[1] = analogRead(A0);
TDistanceArray[2] = 011;
Serial.println(TDistanceArray[1]);

StaticSensePut();


}

void StaticSensePut()
{
  radio.openWritingPipe(Rpipe1);
  //delay(1);
  radio.write( TDistanceArray, sizeof(TDistanceArray) ); 

 
}

