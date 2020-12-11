// NewPing
// Paul Schakel
// Sinusoidally changes the brightness of two LEDs based on the distance value from an ultrasonic sensor. It uses the NewPing library by Tim Eckel.

#include <NewPing.h>

const int echoPin = 2;
const int trigPin = 3;
const int ledPin1 = 9;
const int ledPin2 = 10;
const int maxDistance = 200;
const int offset = 128;    //used to move the value up 128 to account for negative #s coming from sin()
const int amplitude = 127;   //used to amplify the number coming from sin()

int brightness;
int distance;

NewPing myHCSR04(trigPin, echoPin, maxDistance);

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  distance = myHCSR04.ping_cm();

  changeBrightness(ledPin1, distance, 20, '-');
  changeBrightness(ledPin2, distance + 10, 20, '+');
  delay(50);
}

void changeBrightness(int ledPin, int distance, int sineLength, char visualizationChar) {   //changes the brightness of an LED according to the distance from HCSRO4
  brightness = offset + amplitude * sin((TWO_PI / sineLength) * distance);  //distance is the x-value
  visualizeBrightness(brightness, visualizationChar);
  analogWrite(ledPin, brightness);
}

void visualizeBrightness(int brightness, char visualizationChar) {
  brightness = brightness / 6;   //make brightness val smaller so the graph isn't huge
  for (int i = 0; i < brightness; i++) {    //print the specified char for every point of brightness
    Serial.print(visualizationChar);
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
