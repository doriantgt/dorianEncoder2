#ifndef DORIAN_ENCODER2_H
#define DORIAN_ENCODER2_H

#include <sys/_stdint.h>
//SETUP NOTES
//THIS LIBRARY REQUIRES CAPACITORS TO DEBOUNCE ENCODER
//ESP32-S3 pullup resistors 47kohm
//used 10nf caps on both encoder pins
//simply switch declared pins to change direction



/* ENCODER PHASE DIAGRAM
  _v__  _v__
  |' |  |' |
__|' |__|' |__        v
 __'_  __'_       (stop detent)
 | '|  | '|           ^
_| '|__| '|__       the encoder this was written for returns back to the same position each time.
   ^     ^           in other words it steps through all 4 points (phase combinations?) in one rotation step.
*/


class Encoder4phase {
  public:
 volatile int32_t counter=0; //is volatile necissary?
 volatile bool positiveDirection;
 volatile bool negativeDirection;
  uint8_t pinA, pinB;
 #ifdef CHECK_NUM_OF_INTERRUPTS
 volatile uint32_t interruptCounter=0; //number of interrupts should roughly be twice as high as counter
 #endif


 Encoder4phase(uint8_t PinA, uint8_t PinB): pinA(PinA), pinB(PinB) {}


 void encPinAmovement(bool pinBstate){//note opposite pins!

      if(pinBstate){ //store position if complete step
      //  counter+=positiveDirection;
        counter-=negativeDirection;
        positiveDirection = 0;
        negativeDirection = 0;

      }else{ // set direction

        if(negativeDirection){//double back on turn check
          positiveDirection = false;//incomplete turn
          negativeDirection = false;
        }else{ positiveDirection = true; //single step OKAY
        }            
    }

 }
 void encPinBmovement(bool pinAstate){ //note opposite pins!
   
    if(pinAstate){//store value
      counter+=positiveDirection;
     // counter-=negativeDirection;
      positiveDirection = 0;
      negativeDirection = 0;

    }else{ // set direction
    
      if(positiveDirection){//double back on turn check
        positiveDirection = false;//incomplete turn
        negativeDirection = false;
      } else{ negativeDirection =true; //single step OKAY
      }
       
    }
 }
 
  void setupEncoder(){ //capacitor debounce version
      pinMode(pinA, INPUT_PULLUP);
      pinMode(pinB, INPUT_PULLUP);
      attachInterruptArg(digitalPinToInterrupt(pinA), encPinAInterruptRoutine, this, RISING); //you only need 1 pin as the trigger. the other
      attachInterruptArg(digitalPinToInterrupt(pinB), encPinBInterruptRoutine, this, RISING); //you only need 1 pin as the trigger. the other
    }

  private:
  //trampolines so attachInterruptArg can call back into the right instance's encPinAmovement/encPinBmovement
  //defined outside the class body (below) so they aren't implicitly inline -
  //inline IRAM_ATTR functions can trigger "dangerous relocation: l32r: literal placed after use" at link time.
  static void IRAM_ATTR encPinAInterruptRoutine(void* arg);
  static void IRAM_ATTR encPinBInterruptRoutine(void* arg);
};

void IRAM_ATTR Encoder4phase::encPinAInterruptRoutine(void* arg){
  Encoder4phase* self = static_cast<Encoder4phase*>(arg);
  self->encPinAmovement(digitalRead(self->pinB)); //note opposite encoder pin in the argument
  #ifdef CHECK_NUM_OF_INTERRUPTS
  self->interruptCounter++;
  #endif
}
void IRAM_ATTR Encoder4phase::encPinBInterruptRoutine(void* arg){
  Encoder4phase* self = static_cast<Encoder4phase*>(arg);
  self->encPinBmovement(digitalRead(self->pinA));
  #ifdef CHECK_NUM_OF_INTERRUPTS
  self->interruptCounter++;
  #endif
}

#endif