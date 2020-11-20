// Finite LED Blinker
// Paul Schakel
// Goes between 2 LED's fading them in and out a specified number of times with a randomly generated sine wave length.
// The brightness of each LED is represented in the serial monitor with a specified char.

const int ledPin1 = 9;
const int ledPin2 = 10;
const int offset = 128;    //used to move the value up 128 to account for negative #s coming from sin()
const int amplitude = 127;   //used to amplify the number coming from sin()
const int wavesPerLed = 4;
const char led1Char = '-';
const char led2Char = '+';

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  blinkCycle(ledPin1, random(5, 40), led1Char);
  blinkCycle(ledPin2, random(5, 40), led2Char);
}

void blinkCycle(int ledPin, int sineLength, char visualizationChar) {   //goes through one waveCycle with a specified LED
  int counter = 0 - sineLength / 3;    //this counter advances the x-value in the sine wave
  int brightness = 0;
  int cycleCounter = 0;

  while (true) {
    if (cycleCounter >= wavesPerLed) {  //checks to make sure the wavePerLed limit hasn't been reached
      analogWrite(ledPin, 0);
      break;
    } else {
      analogWrite(ledPin, brightness);
      counter++;
      brightness = offset + amplitude * sin((TWO_PI / sineLength) * counter);   //change brightness for next loop
      visualizeBrightness(brightness, visualizationChar);    //visualizes the brightness in the Serial monitor
    }

    if ((counter + sineLength / 3) % sineLength == 0) {   //checks if a wave has been completed
      cycleCounter++;
    }

    delay(150);   //adds delay so the fade happens gradually
  }
}

void visualizeBrightness(int brightness, char visualizationChar) {
  brightness = brightness / 6;   //make brightness val smaller so the graph isn't huge
  for (int i = 0; i < brightness; i++) {    //print the specified char for every point of brightness
    Serial.print(visualizationChar);
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
