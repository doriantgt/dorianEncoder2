
//example written and tested on esp32-s3

#define CHECK_NUM_OF_INTERRUPTS //used to check how much you're interuppts are being triggered.
                                // comment to disable. Note: Encoder4phase has a public variable interruptCounter 
                                // that is only included when CHECK_NUM_OF_INTERRUPTS is delcared.
                                // So Encoder4phase objects will change size depending if you inclde CHECK_NUM_OF_INTERRUPTS or not.
                            

#include "dorianEncoder2.h"


  //for every instance of an encoder you just need 
  //Encoder4phase yourEncoder(pinA, pinB); 
  //and a setupEncoder() call below.

// VOLTAGE+ NOT REQUIRED ON ENCODER SUPPLIED INSTEAD BY PULLUP ON READ PINS
Encoder4phase encoder(2, 1);//pins will be pulled up
//10nf CAPACITOR OR SIMILAR REQUIRED ON BOTH ENCODER PINS.
//ESP32-S3  pullup 45kohm
// VOLTAGE+ NOT REQUIRED ON ENCODER SUPPLIED INSTEAD BY PULLUP ON READ PINS

void setup() {

  Serial.begin(115200);
  encoder.setupEncoder();

  delay(1000);
  Serial.println("is working");
}

void loop() {

  static int lastCounter;

  if(lastCounter != encoder.counter){
  #ifdef CHECK_NUM_OF_INTERRUPTS
  Serial.printf("A counter %i  number of interrupts %i\n" , encoder.counter, encoder.interruptCounter);
  //number of interrupts should roughly twice as high as counter. more is expected but a lot isn't neccisarly bad either
  //intturpts can cause problems with serial.print() fyi
  #else
  Serial.printf("A counter %i\n" , encoder.counter);
  #endif
   }
  lastCounter = encoder.counter;




  delay(1); //watch dog watch out
}