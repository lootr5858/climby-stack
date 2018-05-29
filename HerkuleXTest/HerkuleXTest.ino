#include <Herkulex.h>

int SERVO2 = 2; // front left
int SERVO4 = 4; // front right

int SERVO1 = 1; // back left
int SERVO3 = 3; // back right


float SERVO1_OFFSET = -4.0;
float SERVO2_OFFSET = 0.0;
float SERVO3_OFFSET = 4.0;
float SERVO4_OFFSET = -4.0;

void setup()  
{
  delay(500);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  
  Herkulex.begin(115200,8,7);
  
  Serial.println("Begin");
  delay(500); 
  Herkulex.reboot(SERVO1);
  Herkulex.reboot(SERVO2);
  Herkulex.reboot(SERVO3);
  Herkulex.reboot(SERVO4);
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(1000);

  Herkulex.moveOneAngle(SERVO2, -45, 1000, LED_CYAN);
  Herkulex.moveOneAngle(SERVO4, 45, 1000, LED_CYAN);
  Herkulex.moveOneAngle(SERVO1, 45, 1000, LED_CYAN);
  Herkulex.moveOneAngle(SERVO3, -45, 1000, LED_CYAN);
  delay(1000);
  
  Herkulex.moveOneAngle(SERVO2, 0 + SERVO2_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO4, 0 + SERVO4_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO1, 0 + SERVO1_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO3, 0 + SERVO3_OFFSET, 1000, LED_GREEN);
  
  delay(1000);
}

void loop(){
  Serial.println("Center");
  Herkulex.moveOneAngle(SERVO2, 0 + SERVO2_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO4, 0 + SERVO4_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO1, 0 + SERVO1_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO3, 0 + SERVO3_OFFSET, 1000, LED_GREEN);
  delay(3000);

  Serial.println("90-deg");
  Herkulex.moveOneAngle(SERVO2, -90 + SERVO2_OFFSET, 500, LED_BLUE);
  Herkulex.moveOneAngle(SERVO4, 90 + SERVO4_OFFSET, 500, LED_BLUE);
  Herkulex.moveOneAngle(SERVO1, 90 + SERVO1_OFFSET, 500, LED_BLUE);
  Herkulex.moveOneAngle(SERVO3, -90 + SERVO3_OFFSET, 500, LED_BLUE);
  delay(4000);

  Serial.println("Center");
  Herkulex.moveOneAngle(SERVO2, 0 + SERVO2_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO4, 0 + SERVO4_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO1, 0 + SERVO1_OFFSET, 1000, LED_GREEN);
  Herkulex.moveOneAngle(SERVO3, 0 + SERVO3_OFFSET, 1000, LED_GREEN);
  delay(3000);

  Serial.println("diamond");
  Herkulex.moveOneAngle(SERVO2, -45 + SERVO2_OFFSET, 100, LED_CYAN);
  Herkulex.moveOneAngle(SERVO4, 45 + SERVO4_OFFSET, 100, LED_CYAN);
  Herkulex.moveOneAngle(SERVO1, 45 + SERVO1_OFFSET, 100, LED_CYAN);
  Herkulex.moveOneAngle(SERVO3, -45 + SERVO3_OFFSET, 100, LED_CYAN);
  delay(4000);
}


