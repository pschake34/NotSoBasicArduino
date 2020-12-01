// Variable LED Blink
// Paul Schakel
// Blinks 2 LED's. The first LED blinks increasingly faster, transitions to the second LED, which blinks increasingly slower, transitions to the first LED, and the repeats.

const int ledPin1 = 9;
const int ledPin2 = 10;

int delayVar;
int delayChange;
int delayLimit;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  ledCycle(ledPin1, true);
  transition(ledPin1, ledPin2, 100);
  ledCycle(ledPin2, false);
  transition(ledPin2, ledPin1, 1000);
}

void ledCycle(int led, bool descending) {   //Goes through a descending or ascending sequence with an LED
  if (descending) {
    delayVar = 1000;
    delayChange = -100;
    delayLimit = 100;
  } else {
    delayVar = 100;
    delayChange = 100;
    delayLimit = 1000;
  }

  while (true) {
    digitalWrite(led, HIGH);
    delay(delayVar);
    digitalWrite(led, LOW);
    delay(delayVar);
    delayVar = delayVar + delayChange;

    if (descending && delayVar <= delayLimit) {   //stop clause if descending
      break;
    } else if (!descending && delayVar >= delayLimit) {   //stop clause if not descending
      break;
    }
  }
}

void transition(int led1, int led2, int delayVar) {   //Blinks between 2 LED's with a specified delay
  int counter = 0;
  while (counter < 6) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    delay(delayVar);
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    delay(delayVar);
    counter++;
  }
}