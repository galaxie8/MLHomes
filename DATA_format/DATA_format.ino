String PUSHdata;
String Stemp = "T:";
String Shum = "H:";
String Sfire = "F:";
String Swater = "W:";
String Sdist = "D:";

int temp = 78;
int hum = 40;
int fire = 0;
int water = 1;
int distance = 0;

String StartCMD;
void setup()
{
  Serial.begin(115200);
  Serial.println("starting hackathon project");
}

void loop() 
{
    PUSHdata = Stemp + temp + Shum + hum + Sfire + fire + Swater + water + Sdist + distance;
  if(Serial.available())
  {
    StartCMD = Serial.readString();
    if(StartCMD == "GimmieDaSensors!\r\n")
    {
      Serial.print(PUSHdata);
      Serial.println();
    }
  }
}
