#include <Herkulex.h>

int MOTORID = 253;
int NEW_MOTORID = 4;

int RX = 7;
int TX = 8; 

void setup()  
{
  delay(500);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.begin(115200,RX,TX); //open serial with rx=10 and tx=11 
  Herkulex.reboot(MOTORID); //reboot first motor
  delay(1000); 
  Herkulex.initialize(); //initialize motors
  delay(1000);
  Herkulex.set_ID(MOTORID, NEW_MOTORID);
}

void loop(){
}


