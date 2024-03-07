const int pwmPin=3;
void setup() {
  // put your setup code here, to run once:
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pwmPin, 128);
  delay(500);
}
