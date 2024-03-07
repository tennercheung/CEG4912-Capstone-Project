#include <Servo.h>
#include <arduino-timer.h>
#include <AccelStepper.h>
#define stepPin 2
#define dirPin 3

bool done = false;
char currentBin = 'I';

const int trig_1_Pin = 9;  
const int echo_1_Pin = 8;

const int servoPin = 7;
 
float duration;
float distance_pic;

char S[15];
boolean valid = false;
Servo myservo;  // create servo object to control a servo


void setup() {  
  
  pinMode(trig_1_Pin, OUTPUT);  
  pinMode(echo_1_Pin, INPUT); 

  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);

  myservo.attach(servoPin);  // attaches the servo on pin 7 to the servo object

  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect.
  } 
 
}  


void loop() {  
//  distance_pic = getDistance(trig_1_Pin,echo_1_Pin);

  checkForWasteDump();
  if(getDistance(trig_1_Pin,echo_1_Pin) < 20.0){
    Serial.println("picture");
  }
  delay(50);

 
} 


int stepCalculator(int targetBin, int currentBin){

  int steps;

  switch(targetBin) {
    case 'R':
      targetBin = 50;
      break;
    case 'P':
      targetBin = 150;
      break;
    case 'W':
      targetBin = 250;
      break;
    case 'O':
      targetBin = 350;
      break;
  }

  switch(currentBin) {
    case 'R':
      currentBin = 50;
      break;
    case 'P':
      currentBin = 150;
      break;
    case 'W':
      currentBin = 250;
      break;
    case 'O':
      currentBin = 350;
      break;
  }

  return steps = targetBin - currentBin; 

}


float getDistance(const int trigPin,const int echoPin){

  float dur; 
  float dist;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2);  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(trigPin, LOW);

  dur = pulseIn(echoPin, HIGH);  
  dist = (dur*.0343)/2; 
  
  return dist;
}

void rotateBin(char sort){
  if(currentBin == 'I'){
      switch(sort) {
        case 'R':
          digitalWrite(dirPin,HIGH); 
          for(int x = 0; x < 50; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);   
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = sort;
          done = true;
        break;
        
        case 'P':
          digitalWrite(dirPin,HIGH); 
          for(int x = 0; x < 150; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = sort;
          done = true;
        break;
        
        case 'W':
          digitalWrite(dirPin,LOW); 
          for(int x = 0; x < 150; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);    
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = sort;
          done = true;
        break;
        
        case 'O':
          digitalWrite(dirPin,LOW); 
          for(int x = 0; x < 50; x++) {
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(700);    
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(700); 
          }
          currentBin = sort;
          done = true;
        break;
     }
  }else {
      int steps = stepCalculator(sort,currentBin);

      if(steps > 0){
        digitalWrite(dirPin,HIGH); 
        for(int x = 0; x < steps; x++) {
          digitalWrite(stepPin,HIGH); 
          delayMicroseconds(700);    
          digitalWrite(stepPin,LOW); 
          delayMicroseconds(700);
        }
        currentBin = sort;
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
        currentBin = sort;
        done = true;
      }

      else {
        done = true;
      }
   }
}

boolean checkForWasteDump(){
  char buffer[16];

  if (Serial.available() > 0) {
    int size = Serial.readBytesUntil('\n', buffer, 12);
  
  int endPos = 90;

  if (buffer[0] == 'R') {
    valid = true;
    done = false;
    rotateBin(buffer[0]);
  }
  else if (buffer[0] == 'P') {
    valid = true;
    done = false;
    rotateBin(buffer[0]);
  }
  else if (buffer[0] == 'W') {
    valid = true;
    done = false;
    rotateBin(buffer[0]);
  }
  else if (buffer[0] == 'O') {
    valid = true;
    done = false;
    rotateBin(buffer[0]);
  }
  
  if(valid==true){
    int pos = 0;    // variable to store the servo position

//    delay(500);
    for (pos = 0; pos <= endPos; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
    delay(500);
    for (pos = endPos; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
  valid = false;
    
  }
  
  }
  
  return valid; 
}

  


  
