// Hello Functions
// Paul Schakel
// Reads the distance from an HC-SRO4 ultrasonic sensor, and fades two LEDs in and out depending on the distance.
// If the distance is less than 5cm, both LEDs are off; if the distance is 5cm, one LED will be off and the second will be at full brightness; if the distance is 30cm, the first LED will be at full, and the second will be off.
// As long as the distance is within those constraints, the two LEDs display a brightness proportional to the distance from the servo and inverse of each other.

const int echoPin = 2;
const int trigPin = 3;
const int ledPin1 = 9;
const int ledPin2 = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  distance = getDistance();
  fadeLed(distance, ledPin1, 5, 30);
  fadeLed(distance, ledPin2, 30, 5);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void fadeLed(int distance, int ledPin, int lowerLimit, int upperLimit) {
  if ((distance > lowerLimit && distance < upperLimit) || (lowerLimit > upperLimit && distance < lowerLimit && distance > upperLimit)) {  // this if statement compensates for inverted values but looks ugly
    int brightness = map(distance, lowerLimit, upperLimit, 0, 255);   //maps the distance value to an LED brightness value
    Serial.print("Brightness: ");
    Serial.println(brightness);
    analogWrite(ledPin, brightness);
  } else {
    Serial.println("LED off");
    analogWrite(ledPin, 0);
  }
}

int getDistance() {   //briefly activates the triggerPin to transmit a sound wave, then reads the distance from the echoPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}