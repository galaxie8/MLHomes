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
int RStaticArray[5];  // 2 element array holding data readings
int TStaticArray[5];

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
TStaticArray[0] = 001;
TStaticArray[1] = analogRead(A0);
TStaticArray[2] = analogRead(A1);
TStaticArray[3] = analogRead(A3);
TStaticArray[4] = 001;
}

void StaticSensePut()
{
  radio.openWritingPipe(Rpipe);
  //delay(1);
  radio.write( TStaticArray, sizeof(TStaticArray) );  
}

