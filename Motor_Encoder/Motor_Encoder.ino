#include <Encoder.h>

#define ENC4 1778 //rpm for400mm
#define ENC3 1856 //rpm for 400mm

Encoder myEnc4(32, 31);
Encoder myEnc3(0,1);

void setup() {
  Serial.begin(9600);
}

void loop() {
    float translate_4 = myEnc4.read() * 40;
    translate_4 = translate_4/ENC4;
    float translate_3 = myEnc3.read() * 40;
    translate_3 = translate_3/ENC3;
    //Serial.print("Motor 4: ");
    //Serial.print(translate_4);
    //Serial.print(" Motor 3: ");
    Serial.print(translate_3);
    Serial.println();
    delay(500);

}
