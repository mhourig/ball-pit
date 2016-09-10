const int fsrPin = A0;
float fsrFloat;
String fsrString;

void setup() {
  pinMode(fsrPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0 && Serial.read() == 'r') {
  fsrFloat = analogRead(fsrPin);
  fsrString = String(fsrFloat);
  Serial.print(fsrString);
  Serial.println(" ");
  }

}
