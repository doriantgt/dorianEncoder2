//SETUP NOTES
//THIS REQUIRES CAPACITORS TO DEBOUNCE ENCODER
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

class Encoder {
  public: 
 volatile int32_t counter=0; //is volatile necissary?
 volatile bool positiveDirection;
 volatile bool negativeDirection;

 
 void encAmovement(bool encBstate){//note opposite pins!

      if(encBstate){ //store position if complete step
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
 void encBmovement(bool encAstate){ //note opposite pins!
   
    if(encAstate){//store value
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
 
  void setupEncoder(uint8_t encA, uint8_t encB, void (*interruptRoutineA)(), void (*interruptRoutineB)()){ //capacitor debounce version
      pinMode(encA, INPUT_PULLUP);
      pinMode(encB, INPUT_PULLUP);   
      attachInterrupt(digitalPinToInterrupt(encA), interruptRoutineA, RISING); //you only need 1 pin as the trigger. the other 
      attachInterrupt(digitalPinToInterrupt(encB), interruptRoutineB, RISING); //you only need 1 pin as the trigger. the other  
    }
};
