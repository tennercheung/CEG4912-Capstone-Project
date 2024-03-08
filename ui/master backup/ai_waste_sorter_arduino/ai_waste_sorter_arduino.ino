

#include <Servo.h>


#include <arduino-timer.h>

//#include "string.h"


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

  myservo.attach(servoPin);  // attaches the servo on pin 7 to the servo object
//  bin_1_timer.every(5000,checkBin(1)); // Set up to trigger every x milliseconds 
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect.
  } 
 

 
}  



void loop() {  
  
//  bin_1_timer.tick(); //run timer for bin_1
//  distance_pic = getDistance(trig_1_Pin,echo_1_Pin);

//  if (valid==false){
    checkForWasteDump();
    if(getDistance(trig_1_Pin,echo_1_Pin) < 10.0){
      Serial.println("picture");
//    while(true){/
      
//      if(valid==true){
//        valid = false;
//        break;
//      }
//    }
    
    }
    
//  }/

  delay(50);

 
} 
//int checkBin(int binID){
//  float distance_bin;
//  float weight_bin;  
//  if(binID==1){
//    distance_bin = getDistance(trig_2_Pin,echo_2_Pin);
//    weight_bin = scale_1_read();
//    
//    
////    char str1[15] = to_string(distance_bin);
////    Serial.println(FloatToString(String s1, distance_bin));
//  }
//  return 0;
//}
//float scale_1_read(){
//  scale_1.set_scale(calibration_factor); //Adjust to this calibration factor
// 
////  if(Serial.available())
////  {
////    char temp = Serial.read();
////    if(temp == '+' || temp == 'a')
////      calibration_factor += 10;
////    else if(temp == '-' || temp == 'z')
////      calibration_factor -= 10;
////  }
//  float weight = scale_1.get_units();
//  return weight;
//}

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


boolean checkForWasteDump(){
  char buffer[16];

  if (Serial.available() > 0) {
    int size = Serial.readBytesUntil('\n', buffer, 12);


  
  int endPos = 90;

  if (buffer[0] == 'R') {
    valid = true;
    
//    Serial.println("recycling");/
  }
  else if (buffer[0] == 'P') {
    valid = true;
    
//    Serial.println("paper");/
  }
  else if (buffer[0] == 'W') {
    valid = true;
    
//    Serial.println("waste");/
  }
  else if (buffer[0] == 'O') {
    valid = true;
    
//    Serial.println("other");/
  }
  
  if(valid==true){
    int pos = 0;    // variable to store the servo position


    
//    rotateBin();
    delay(500);
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

    
  }
  
  }
  
  return valid; 
}
  


  
