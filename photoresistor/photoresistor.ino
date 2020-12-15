// Photoresistor
// Paul Schakel
// Reads the light level from a photoresistor, and checks if the light level is below 20. If so, it turns on an LED which slowly gets brighter as the light level goes down.

const int ledPin = 10;
const int photoRes = A0;

int lightLevel;
int brightness;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(photoRes, INPUT);
  Serial.begin(9600);
}

void loop() {
  lightLevel = analogRead(photoRes);
  if (lightLevel < 20) {  //turn on LED
    brightness = map(lightLevel, 20, 0, 0, 255);  //makes the LED brighter depending on the light level
    Serial.println(brightness);
    analogWrite(ledPin, brightness);
  } else {  //turn off LED
    analogWrite(ledPin, 0);
  }
}
