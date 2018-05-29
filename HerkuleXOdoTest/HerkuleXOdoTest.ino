#include <Herkulex.h>

int SERVO = 2;

int RX = 8;
int TX = 7; 

void setup()
{
  delay(500);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.begin(115200, RX, TX);
  Herkulex.reboot(SERVO);
  delay(1000);
  Herkulex.initialize(); //initialize motors
  delay(1000);
  Herkulex.moveOneAngle(SERVO, 100, 500, LED_CYAN);
  delay(1000);
  Herkulex.moveOneAngle(SERVO, 0, 500, LED_GREEN);
  delay(1000);
}

void loop() {
  Herkulex.moveOneAngle(SERVO, 0, 500, LED_GREEN);
  delay(1000);
}


