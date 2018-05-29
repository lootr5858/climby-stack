#include <Herkulex.h>
#include <SoftwareSerial.h>


int servo_front_left = 2; // SERVO 2 initially
int servo_front_right = 4; // SERVO 4

int servo_back_left = 1; // SERVO 1
int servo_back_right = 3; // SERVO 3


float offset_back_left = -4.0; // SERVO 1_OFFSET
float offset_front_left = 0.0; // SERVO 2_OFFSET
float offset_back_right = 4.0; // SERVO 3_OFFSET
float offset_front_right = -4.0; // SERVO 4_OFFSET


//----- Serial Config -----//
const byte buffSize = 64;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;
char messageFromPC[buffSize] = {0};
//----- End of Serial Config -----//

int angle;
char ignore;

void posi1(int angle) {
  Herkulex.moveOneAngle(servo_front_left, -180 + angle + offset_front_left, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_front_right, angle + offset_front_right, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_back_left, angle + offset_back_left, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_back_right, -180 + angle + offset_back_right, 700, LED_BLUE);
}

void posi2(int angle) {
  Herkulex.moveOneAngle(servo_front_left, angle + offset_front_left, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_front_right, angle + offset_front_right, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_back_left, angle + offset_back_left, 700, LED_BLUE);
  Herkulex.moveOneAngle(servo_back_right, angle + offset_back_right, 700, LED_BLUE);
}



void getDataFromPC() {
  // receive data from PC and save it into inputBuffer
  if (Serial.available() > 0) {
    char x = Serial.read();
    // the order of these IF clauses is significant
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    if (readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }
    if (x == startMarker) {
      bytesRecvd = 0;
      readInProgress = true;
    }
  }
}

void parseData() {
  char * strtokIndx; // this is used by strtok() as an index
  strtokIndx = strtok(inputBuffer, ",");
  angle = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  ignore = atof(strtokIndx);
}

void replyToPC() {
  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<angle: ");
    Serial.print(angle);
    Serial.print(" ignore: ");
    Serial.print(ignore);
    Serial.println(">");
  }
}

void setup() {
  
  delay(700);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  delay(10);
  Serial.println("<Arduino is ready>");
  
  Herkulex.begin(115200,8,7);
  
  Serial.println("Begin");
  delay(700); 
  Herkulex.reboot(servo_back_left);
  Herkulex.reboot(servo_front_left);
  Herkulex.reboot(servo_back_right);
  Herkulex.reboot(servo_front_right);
  delay(700); 
  Herkulex.initialize(); //initialize motors
  delay(700);

  Herkulex.moveOneAngle(servo_front_left, -45, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_front_right, 45, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_left, 45, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_right, -45, 700, LED_CYAN);
  delay(700);
  
  Herkulex.moveOneAngle(servo_front_left, 0 + offset_front_left, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_front_right, 0 + offset_front_right, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_left, 0 + offset_back_left, 700, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_right, 0 + offset_back_right, 700, LED_CYAN);
  
  delay(700);

  //swing_swing();
  //center();
  Serial.println("Center");
  Herkulex.moveOneAngle(servo_front_left, 0 + offset_front_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_front_right, 0 + offset_front_right, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_left, 0 + offset_back_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_right, 0 + offset_back_right, 700, LED_GREEN);
  delay(3000);
  
}


void loop(){




  getDataFromPC();
  replyToPC();

  if (angle < 90 && angle > 0) 
  { posi1(angle); };
  
  if (angle == 0) 
  {
  Herkulex.moveOneAngle(servo_front_left, 0 + offset_front_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_front_right, 0 + offset_front_right, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_left, 0 + offset_back_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_right, 0 + offset_back_right, 700, LED_GREEN);  };

  if (angle == 90 || angle == -90) 
  {
  Herkulex.moveOneAngle(servo_front_left, -90 + offset_front_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_front_right, 90 + offset_front_right, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_left, 90 + offset_back_left, 700, LED_GREEN);
  Herkulex.moveOneAngle(servo_back_right, -90 + offset_back_right, 700, LED_GREEN);  };

  if (angle > 90 && angle < 160)
  { posi2(angle); };

    if (angle < 0 && angle > -160 ) 
  { angle = 180 - -angle ;};

  if (angle>159 || angle<-159) 
  {
  Serial.println("diamond");
  Herkulex.moveOneAngle(servo_front_left, -45 + offset_front_left, 200, LED_CYAN);
  Herkulex.moveOneAngle(servo_front_right, 45 + offset_front_right, 200, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_left, 45 + offset_back_left, 200, LED_CYAN);
  Herkulex.moveOneAngle(servo_back_right, -45 + offset_back_right, 200, LED_CYAN);};
  
  
 // if (angle == 0 || speed > 12 || speed < -12) {
 //   brake();
 // };
 
}
