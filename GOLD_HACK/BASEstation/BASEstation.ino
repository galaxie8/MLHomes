
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const uint64_t Tpipe = 0xE8E8F0F0E1LL; // Define the transmit pipe
const uint64_t Rpipe = 0xF0F0F0F0E1LL;  // Define the receive pipe

RF24 radio(CE_PIN, CSN_PIN);

int Rarray[4];  // 2 element array holding incoming data
int Tarray[2]; // 2 element array holding outgoig data

String PUSHdata;
String StartCMD;
String Stemp = "T";
String Shum = ":H";
String Sfire = ":F";
String Swater = ":W";


void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(115200);
  Serial.println("Let the hacking begin!");
  delay(1000);
  radio.begin();
  radio.setRetries(0,15);
}//--(end setup )---


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{  
  sendsensor();
  getdat();
  //results();
  
   PUSHdata = Stemp + Rarray[2] + Shum + Rarray[3] + Sfire + Rarray[0] + Swater + Rarray[1];
  if(Serial.available())
  {
    StartCMD = Serial.readString();

    if(StartCMD == "GimmieDaSensors!\r\n")
    {
      Serial.print(PUSHdata);
      Serial.println();
    }
    
    if(StartCMD == "ToggleLight!\r\n")
    {
      if(Tarray[1] == 0)
      {
      Tarray[1] = 1;
      }
      else
      Tarray[1] = 0;
    }
 
  
  }
}
///////////////////////////////////////////////////////////////

void sendsensor()
{
Tarray[0] = 330; 
 radio.openWritingPipe(Rpipe);
  //delay(1);
  radio.write( Tarray, sizeof(Tarray) ); 
}
///////////////////////////////////////////////////////////////
void getdat()
{
  radio.openReadingPipe(1,Tpipe);
  radio.startListening();
  delay(1);
  if ( radio.available() )
  {  
      // Read the data payload
     radio.read( Rarray, sizeof(Rarray) );
  }
   radio.stopListening();
}

///////////////////////////////////////////////////////////////
 void results()
 {
      Serial.print("Fire = ");
      Serial.println(Rarray[0]);
      Serial.print("Water = ");      
      Serial.println(Rarray[1]);    
      Serial.print("Temp = ");      
      Serial.println(Rarray[2]); 
      Serial.print("Humidity = ");      
      Serial.println(Rarray[3]);   
      Serial.println(); 
 }

