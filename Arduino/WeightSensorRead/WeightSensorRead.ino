/*

 Arduino pin 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND
 
 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
#include <arduino-timer.h>

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2



HX711 scale_1;
auto scale_1_timer = timer_create_default();

float calibration_factor = -485; 

void setup() {

  
  scale_1_timer.every(1000,scale_1_read); // Set up to trigger every 1000 milliseconds (1 second)
  
  Serial.begin(9600);
  
//  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {
  scale_1_timer.tick(); //run timer for scale_1
  
}

void scale_1_read(){
  scale_1.set_scale(calibration_factor); //Adjust to this calibration factor
  
  Serial.print("Reading: ");
  Serial.print(scale_1.get_units(), 2);
  Serial.print(" g"); 
  Serial.println();

//  if(Serial.available())
//  {
//    char temp = Serial.read();
//    if(temp == '+' || temp == 'a')
//      calibration_factor += 10;
//    else if(temp == '-' || temp == 'z')
//      calibration_factor -= 10;
//  }
}
