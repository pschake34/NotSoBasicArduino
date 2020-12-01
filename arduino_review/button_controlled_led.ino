// Button Controlled LED
// Paul Schakel
// Blinks 1 LED while a button is pressed. The LED starts blinking with a delay of 1000ms and blinks increasingly faster so that the delay goes down by 100ms every time loop() is called.
// Once the delay reaches 100ms, the LED blinks 20 times at 100ms, and then blinks increasingly slowly until the delay reaches 1000ms. 
// This loop continues as long as the button is pressed, and pauses when the button is unpressed

const int ledPin = 9;
const int btnPin = 10;

//defines the initial values for the first blinking cycle
int delayVar = 1000;
int delayChange = -100;
int delayLimit = 100;
int buttonState = 0;
int fastBlinkCounter = 0;
bool descending = true;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
}

void loop() {
  buttonState = digitalRead(btnPin);

  if (buttonState == HIGH) {
    Serial.print("LED is blinking with a delay of ");
    Serial.println(delayVar);
    digitalWrite(ledPin, HIGH);
    delay(delayVar);
    digitalWrite(ledPin, LOW);
    delay(delayVar);
    delayVar = delayVar + delayChange;    //changes the delay for the next loop

    if (descending && delayVar <= delayLimit) {   //stop clause if descending
      fastBlinkCounter++;
      delayChange = 0;
      if (fastBlinkCounter >= 20) {   //makes sure that the LED has blinked fast long enough, and begins the increasing delay
        delayVar = 100;
        delayChange = 100;
        delayLimit = 1000;
        descending = false;
        fastBlinkCounter = 0;
      }
    } else if (!descending && delayVar >= delayLimit) {   //stop clause if ascending
      delayVar = 1000;
      delayChange = -100;
      delayLimit = 100;
      descending = true;
    }
  } else {
    Serial.println("LED is not blinking");
    delay(250);
  }
}
