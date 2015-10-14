#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <dht.h>
dht DHT;

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t Tpipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
const uint64_t Rpipe = 0xF0F0F0F0E1LL;  // Define the receive pipe

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

int Rarray[4];  // 2 element array holding outgoing data
int Tarray[2]; // 2 element array holding incoming data

const int TempS = 2;
const int FireS = A0;
const int WaterS = A1;
const int LED = 3;
int temp;
int Ftemp;
int humid;
int Afire, Awater;
boolean fire = false;
boolean water = false;

void setup()   /****** SETUP: RUNS ONCE ******/
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(0,15);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  getsensor();
  senddat();
  getdat();
  results();

}//--(end main loop )---

void getsensor()
{
 DHT.read11(2);
 temp = DHT.temperature;
 humid = DHT.humidity;
 Ftemp = temp * 1.8;
 Ftemp += 32;
 Afire = analogRead(FireS); 
 Awater = analogRead(WaterS);
 Rarray [2] = Ftemp;
 Rarray [3] = humid;
 /////////////////////////////
 if(Awater > 400)
 {
 water = true;
 }
 else
 {
 water = false;
 }
//////////////////////////////////// 
 if(Afire < 150)
 {
 fire = true;
 }
 else
 {
 fire = false;
 }
 //////////////////////////////////////////
}
void getdat()
{
  radio.openReadingPipe(1,Rpipe);
  radio.startListening();
  delay(1);
  if ( radio.available() )
  {  
     // Read the data payload
     radio.read( Tarray, sizeof(Tarray) );  
  }
  radio.stopListening();
}

void senddat()
{
 Rarray [0] = fire;
 Rarray [1] = water;
 Rarray [2] = Ftemp;
 Rarray [3] = humid;
  radio.openWritingPipe(Tpipe);
  //delay(1);
  radio.write( Rarray, sizeof(Rarray) );
  
}

void results()
{
        for(int i=0; i<2; i++)
        {
        Serial.println(Tarray[i]);
        }  
         Serial.println();
         
         if(Tarray[1] == 1)//triger for lamp
           digitalWrite(LED,1);
         else
         digitalWrite(LED,0);

         
}
