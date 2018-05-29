#include <SoftwareSerial.h>
#include <Encoder.h>

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

int distance = 0;
int speed;
char ignore;

#define ENC4 1856 //RPM for motor 4 along 40cm
#define ENC3 1778 //RPM for motor 3 along 40cm
Encoder myEnc4(1,0);
Encoder myEnc3(31, 32);
float translate_4;
float translate_3;
float later;

long previousMillis = 0;
long interval = 1000; // 1 sec  
void read_encoder(){
  translate_4 = myEnc4.read() * 40;
  translate_4 = translate_4/ENC4;
  translate_3 = myEnc3.read() * 40;
  translate_3 = translate_3/ENC3;

  unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis > interval) 
  {previousMillis = currentMillis; // save the last time you printed
  Serial.print("Motor 4: ");
  Serial.print(translate_4);
  Serial.print(" Motor 3: ");
  Serial.print(translate_3);
  Serial.println();

  later = (translate_4 + translate_3)/2 ; // update
} }

void forward(int pwm) {
  analogWrite(9, pwm);
  digitalWrite(28, HIGH);
  digitalWrite(29, LOW);

  analogWrite(10, pwm);
  digitalWrite(26, HIGH);
  digitalWrite(27, LOW);

}

void brake() {
  digitalWrite(9, HIGH);
  digitalWrite(28, HIGH);
  digitalWrite(29, HIGH);

  digitalWrite(10, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(27, HIGH);

}

void backward(int pwm) {
  analogWrite(9, pwm);
  digitalWrite(28, LOW);
  digitalWrite(29, HIGH);

  analogWrite(10, pwm);
  digitalWrite(26, LOW);
  digitalWrite(27, HIGH);
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
  //speed = atof(strtokIndx);
  distance = atof(strtokIndx);
  strtokIndx = strtok(NULL, ",");
  ignore = atof(strtokIndx);
}

void replyToPC() {
  if (newDataFromPC) {
    newDataFromPC = false;
    Serial.print("<speed: ");
    //Serial.print(speed * 10);
    Serial.print(distance);
    Serial.print(" ignore: ");
    Serial.print(ignore);
    Serial.println(">");
  }
}

void setup() {
  pinMode(12, OUTPUT); // STANDBY
  digitalWrite(12, LOW);

  pinMode(10, OUTPUT); // PWM A
  pinMode(26, OUTPUT); // MOTOR A
  pinMode(27, OUTPUT);

  pinMode(9, OUTPUT); // PWM B
  pinMode(28, OUTPUT);  // MOTOR B
  pinMode(29, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
  delay(10);
  speed = 0;
  Serial.println("<Arduino is ready>");

  digitalWrite(12, HIGH);

}



// the loop function runs over and over again forever
void loop() {
  getDataFromPC();
  replyToPC();
  if (distance != 0){
      float curr = (translate_4 + translate_3)/2; // avg = current position
      if (distance > 0){
        while (abs(later- curr) < distance){
          Serial.println(abs(later-curr));
          read_encoder();
          forward(50);
        }
        distance = 0;
        brake();
      }
      else{
        distance = -1 * distance;
        while (abs(later- curr) < distance){
          Serial.println(abs(later-curr));
          read_encoder();
          backward(50);
        }
        distance = 0;
        brake();
      }
  }
  
  //if (speed < 12 && speed > 0) {
  //      forward(speed*10); };
  //if (speed > -12 && speed < 0) {
  //      backward(speed*10); };
  //if (speed == 0 || speed > 12 || speed < -12) {
  //  brake(); };
  
  read_encoder();
}

