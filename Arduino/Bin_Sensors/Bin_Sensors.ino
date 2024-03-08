
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711
#include <arduino-timer.h>

#define LOADCELL_R_DOUT_PIN  3
#define LOADCELL_R_SCK_PIN  2

/*adjust names and values*/
#define LOADCELL_P_DOUT_PIN  5
#define LOADCELL_P_SCK_PIN  4

#define LOADCELL_W_DOUT_PIN  7
#define LOADCELL_W_SCK_PIN  6

#define LOADCELL_O_DOUT_PIN  9
#define LOADCELL_O_SCK_PIN  8

/*add the correct values*/
const int trig_O_Pin = 19;  
const int echo_O_Pin = 18;

const int trig_W_Pin = 17;  
const int echo_W_Pin = 16;

const int trig_P_Pin = 15;  
const int echo_P_Pin = 14;

const int trig_R_Pin = 11;  
const int echo_R_Pin = 10;

float weight_R = 0.00; //recycling "bin 1"
float height_R = 0.0;

float weight_P = 0.00; //paper "bin 2"
float height_P = 0.0;

float weight_W = 0.00; //waste "bin 3"
float height_W = 0.0;

float weight_O = 0.00; //other "bin 4"
float height_O = 0.0;

char grams[] = "g & ";
char centimeters[] = "cm - ";

char bin_R_ID[] = "Bin-R";
char bin_P_ID[] = "Bin-P";
char bin_W_ID[] = "Bin-W";
char bin_O_ID[] = "Bin-O";

char weight_R_str[10];
char height_R_str[10];

char weight_P_str[10];
char height_P_str[10];

char weight_W_str[10];
char height_W_str[10];

char weight_O_str[10];
char height_O_str[10];

char result[40]; // Ensure this is large enough

int min_str_width_weight = 4;
int min_str_width_height = 2;

int decimal_prec = 2;

//add timer to run every 100ms

HX711 scale_R;
HX711 scale_P;
HX711 scale_W;
HX711 scale_O;

auto sensor_read_timer = timer_create_default();

float calibration_factor = -485; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  pinMode(trig_R_Pin, OUTPUT);  
  pinMode(echo_R_Pin, INPUT); 
  pinMode(trig_P_Pin, OUTPUT);  
  pinMode(echo_P_Pin, INPUT);
  pinMode(trig_W_Pin, OUTPUT);  
  pinMode(echo_W_Pin, INPUT); 
  pinMode(trig_O_Pin, OUTPUT);  
  pinMode(echo_O_Pin, INPUT);

  /* Set up timer trigger sensor readings every 500 milliseconds */
  sensor_read_timer.every(500,readSensorData); 

  /*Set up weight sensors*/
  scale_R.begin(LOADCELL_R_DOUT_PIN, LOADCELL_R_SCK_PIN); 
  scale_R.set_scale();
  scale_R.tare();  //Reset the scale to 0

  scale_P.begin(LOADCELL_P_DOUT_PIN, LOADCELL_P_SCK_PIN); 
  scale_P.set_scale();
  scale_P.tare();  //Reset the scale to 0

  scale_W.begin(LOADCELL_W_DOUT_PIN, LOADCELL_W_SCK_PIN); 
  scale_W.set_scale();
  scale_W.tare();  //Reset the scale to 0

  scale_O.begin(LOADCELL_O_DOUT_PIN, LOADCELL_O_SCK_PIN); 
  scale_O.set_scale();
  scale_O.tare();  //Reset the scale to 0
  long zero_factor = scale_R.read_average(); //Get a baseline reading

}

float scale_R_read(){
  scale_R.set_scale(calibration_factor); //Adjust to this calibration factor
 
//  if(Serial.available())
//  {
//    char temp = Serial.read();
//    if(temp == '+' || temp == 'a')
//      calibration_factor += 10;
//    else if(temp == '-' || temp == 'z')
//      calibration_factor -= 10;
//  }
  float weight = scale_R.get_units();
  return weight;
}

float scale_P_read(){
  scale_P.set_scale(calibration_factor); //Adjust to this calibration factor
 
  float weight = scale_P.get_units();
  return weight;
}
float scale_W_read(){
  scale_W.set_scale(calibration_factor); //Adjust to this calibration factor
  
  float weight = scale_W.get_units();
  return weight;
}
float scale_O_read(){
  scale_O.set_scale(calibration_factor); //Adjust to this calibration factor
 

  float weight = scale_O.get_units();
  return weight;
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

void readSensorData(){

  /* Bin R */
  /* weight sensor reading & ultrasonic reading*/
  weight_R = scale_R_read();
  height_R = getDistance(trig_R_Pin,echo_R_Pin);

  /* float to char arr conversion*/
  //params: dtostrf(input float, min width result string, num digits after decimal, output str)
  dtostrf(weight_R, min_str_width_weight, decimal_prec, weight_R_str);
  dtostrf(height_R, min_str_width_height, decimal_prec, height_R_str); 

  /* str concatentation & Serial send*/
  sprintf(result, "%s%s%s%s%s", weight_R_str, grams, height_R_str, centimeters, bin_R_ID);
  Serial.println(result);


  /* Bin P */
  weight_P = scale_P_read();
  height_P = getDistance(trig_P_Pin,echo_P_Pin);

  dtostrf(weight_P, min_str_width_weight, decimal_prec, weight_P_str);
  dtostrf(height_P, min_str_width_height, decimal_prec, height_P_str); 
  
  sprintf(result, "%s%s%s%s%s", weight_P_str, grams, height_P_str, centimeters, bin_P_ID);
  Serial.println(result);


  /* Bin W */
  weight_W = scale_W_read();
  height_W = getDistance(trig_W_Pin,echo_W_Pin);

  dtostrf(weight_W, min_str_width_weight, decimal_prec, weight_W_str);
  dtostrf(height_W, min_str_width_height, decimal_prec, height_W_str); 
  
  sprintf(result, "%s%s%s%s%s", weight_W_str, grams, height_W_str, centimeters, bin_W_ID);
  Serial.println(result);


  /* Bin O */
  weight_O = scale_O_read();
  height_O = getDistance(trig_O_Pin,echo_O_Pin);

  dtostrf(weight_O, min_str_width_weight, decimal_prec, weight_O_str);
  dtostrf(height_O, min_str_width_height, decimal_prec, height_O_str); 
  
  sprintf(result, "%s%s%s%s%s", weight_O_str, grams, height_O_str, centimeters, bin_O_ID);
  Serial.println(result);
}


void loop() {
  
  //run timer
  sensor_read_timer.tick(); 

}
