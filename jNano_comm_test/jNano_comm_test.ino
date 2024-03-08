void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect.
  } 
}

void loop() {

    Serial.println("bin1");
    delay(500);
    Serial.println("bin2");
    delay(500);
    Serial.println("picture");
    delay(500);

}
