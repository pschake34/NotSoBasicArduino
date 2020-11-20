// LED Blink Revisited
// Paul Schakel
// Sinusoidally fades the brightness of an LED, and visualizes the brightness in the serial monitor. 
// The sine function which controls the brightness can be controlled by manipulating the variables below.

//define constants
const int ledPin = 9;
const int offset = 128;    //moves the value up 128 to account for negative #s coming from sin()
const int amplitude = 127;   //used to amplify the number coming from sin()
const int length = 30;   //controls the length of the sine wave

int counter = 0;    //used to advance the x-value of the sine wave
int brightness;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  analogWrite(ledPin, brightness);
  counter++;
  brightness = offset + amplitude * sin((TWO_PI / length) * counter);   //change brightness for next loop
  visualizeBrightness(brightness);    //visualizes the brightness in the Serial monitor
  delay(150);   //adds delay so the fade happens gradually
}

void visualizeBrightness(int brightness) {
  brightness = brightness / 6;   //make brightness val smaller so the graph isn't huge
  for (int i = 0; i < brightness; i++) {    //print "=" for every point of brightness
    Serial.print("=");
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
