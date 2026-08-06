
//example written and tested on esp32-s3
#include "dorianEncoder2.h"



  //for every instance of an encoder you need everything bellow.
  // so the most annoying part is creating the interrupt routines
#define ENC_A 2   //10nf CAPACITOR OR SIMILAR REQUIRED ON BOTH ENCODER PINS.
#define ENC_B 1   //ESP32-S3  pullup 45kohm
// VOLTAGE+ NOT REQUIRED ON ENCODER SUPPLIED INSTEAD BY PULLUP ON READ PINS

Encoder encoder;

 static void IRAM_ATTR encAInterruptRoutine() { //intereupt for pinA and function for pinA
  encoder.encAmovement(digitalRead(ENC_B)); //note oppotite encoder pin in the argument
 }
  static void IRAM_ATTR encBInterruptRoutine() { 
  encoder.encBmovement(digitalRead(ENC_A));
 }

void setup() {

  Serial.begin(115200);
  encoder.setupEncoder(ENC_A, ENC_B,encAInterruptRoutine,encBInterruptRoutine); //ab ab

}

void loop() {

  static int lastCounter;

  if(lastCounter != encoder.counter){
  Serial.printf("counter %i  \n" , encoder.counter);}
  lastCounter = encoder.counter;

  delay(1); //watch dog watch out
}
