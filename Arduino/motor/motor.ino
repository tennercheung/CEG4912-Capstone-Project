// defines pins
#include <AccelStepper.h>
#define stepPin 2
#define dirPin 3

int stepCalculator(int targetBin, int currentBin){

  int steps;

  switch(targetBin) {
    case 1:
      targetBin = 200;
      break;
    case 2:
      targetBin = 600;
      break;
    case 3:
      targetBin = 1000;
      break;
    case 4:
      targetBin = 1400;
      break;
  }

  switch(currentBin) {
    case 1:
      currentBin = 200;
      break;
    case 2:
      currentBin = 600;
      break;
    case 3:
      currentBin = 1000;
      break;
    case 4:
      currentBin = 1400;
      break;
  }

  return steps = targetBin - currentBin; 

}

void setup() {
  // Sets the two pins as Outputs
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}

bool done = false;
int currentBin = 3;
int targetBin = 1;

void loop() {
  
  while(done == false){
    if(currentBin == 0){
      switch(targetBin) {
        case 1:
          digitalWrite(dirPin,HIGH); 
          for(int x = 0; x < 200; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);   
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          done = true;
        break;
        case 2:
          digitalWrite(dirPin,HIGH); 
          for(int x = 0; x < 600; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = targetBin;
          done = true;
        break;
        case 3:
          digitalWrite(dirPin,LOW); 
          for(int x = 0; x < 600; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);    
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = targetBin;
          done = true;
        break;
        case 4:
          digitalWrite(dirPin,LOW); 
          for(int x = 0; x < 200; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);    
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = targetBin;
          done = true;
        break;
     }
   } 
  
    else {
      int steps = stepCalculator(targetBin,currentBin);

      if(steps > 0){
        digitalWrite(dirPin,HIGH); 
        for(int x = 0; x < steps; x++) {
          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(700);    
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(700);
        }
        currentBin = targetBin;
        done = true;
      }

      else if(steps < 0){
        digitalWrite(dirPin,LOW); 
        for(int x = 0; x < abs(steps); x++) {
          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(700);    
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(700);
        }
        currentBin = targetBin;
        done = true;
      }

      else {
        done = true;
      }
    }
  }

  // if(currentBin == 0){
  //   switch(targetBin) {
  //     case 1:
  //         digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
  //         for(int x = 0; x < 25; x++) {
  //           digitalWrite(stepPin,HIGH); 
  //           delayMicroseconds(700);    // by changing this time delay between the steps we can change the rotation speed
  //           digitalWrite(stepPin,LOW); 
  //           delayMicroseconds(700); 
  //         }
  //         currentBin = targetBin;
  //         return done = true;
  //       break;
  //     case 2:
  //         digitalWrite(dirPin,HIGH); 
  //         for(int x = 0; x < 75; x++) {
  //           digitalWrite(stepPin,HIGH); 
  //           delayMicroseconds(700); 
  //           digitalWrite(stepPin,LOW); 
  //           delayMicroseconds(700); 
  //         }
  //         currentBin = targetBin;
  //         return done = true;
  //       break;
  //     case 3:
  //         digitalWrite(dirPin,HIGH); 
  //         for(int x = 0; x < 125; x++) {
  //           digitalWrite(stepPin,HIGH); 
  //           delayMicroseconds(700);    
  //           digitalWrite(stepPin,LOW); 
  //           delayMicroseconds(700); 
  //         }
  //         currentBin = targetBin;
  //         return done = true;
  //       break;
  //     case 4:
  //         digitalWrite(dirPin,HIGH); 
  //         for(int x = 0; x < 175; x++) {
  //           digitalWrite(stepPin,HIGH); 
  //           delayMicroseconds(700);    
  //           digitalWrite(stepPin,LOW); 
  //           delayMicroseconds(700); 
  //         }
  //         currentBin = targetBin;
  //         return done = true;
  //       break;
  //   }
  // } 
  
  // else {
  //     int steps = stepCalculator(targetBin,currentBin);

  //     if(steps > 0){
  //       digitalWrite(dirPin,HIGH); 
  //       for(int x = 0; x < steps; x++) {
  //         digitalWrite(stepPin,HIGH); 
  //         delayMicroseconds(700);    
  //         digitalWrite(stepPin,LOW); 
  //         delayMicroseconds(700);
  //       }
  //       currentBin = targetBin;
  //       return done = true;
  //     }

  //     else if(steps < 0){
  //       digitalWrite(dirPin,LOW); 
  //       for(int x = 0; x < abs(steps); x++) {
  //         digitalWrite(stepPin,HIGH); 
  //         delayMicroseconds(700);    
  //         digitalWrite(stepPin,LOW); 
  //         delayMicroseconds(700);
  //       }
  //       currentBin = targetBin;
  //       return done = true;
  //     }

  //     else {
  //       return done = true;
  //     }


}
