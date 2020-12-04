# NotSoBasicArduino

This repository includes all of my projects from NotSoBasicArduino. Each project has its own folder, which contains project files, circuit diagrams, and a
backup of the code, just in case Arduino Create goes away.

## Table of Contents

* [LED_Fade](#LED_Fade)
* [Finite_LED_Blinker](#Finite_LED_Blinker)
* [Arduino Review](#arduino-review)
* [Hello_Functions](#Hello_Functions)

<br>
<br>

## LED_Fade

### Description & Code

This project accomplishes two things - making an LED fade in and out sinusoidally, and visualizing the brightness of the LED in the serial monitor. My 
code contains two main functions: one which controls the variation of the brightness, and another which visualizes the brightness in the serial monitor.

##### Variation of brightness

```C++
void loop() {
  analogWrite(ledPin, brightness);
  counter++;
  brightness = offset + amplitude * sin((TWO_PI / length) * counter);   //change brightness for next loop
  visualizeBrightness(brightness);    //visualizes the brightness in the Serial monitor
  delay(150);   //adds delay so the fade happens gradually
}
```

Basically, the counter goes up by one every time through the loop. The counter is then fed into the sine function as the x-value. **offset** and 
**amplitude** are constants which have been set up to constrain the sine wave to the proper values. **length** controls the size of the sine wave 
-- smaller values make the wave smaller, and vise versa.

##### Visualization of brightness

```C++
void visualizeBrightness(int brightness) {
  brightness = brightness / 6;   //make brightness val smaller so the graph isn't huge
  for (int i = 0; i < brightness; i++) {    //print "=" for every point of brightness
    Serial.print("=");
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
```

The brightness is divided by 6 so that the graph isn't quite so large, then a for loop prints "=" for each point of brightness. At the end, it prints ">",
which also creates a newline so that the next brightness visualization will be a line lower.

### Evidence

[Code in Arduino Create](https://create.arduino.cc/editor/pschake34/4d8e394c-59cf-47a7-9e31-5b1134052651)

[Project Folder](/led_fade)

### Images

**The Wiring for LED Fade**

<img src="/led_fade/wiring/wiring.png" height=360px alt="LED Fade Wiring">

<br>

**Demonstration of working project**

<img src="/led_fade/demo_video/demo.gif" height=360px alt="LED Fade Demo">

### Reflection

This being the first code project, it took me a bit of time to get back in the swing of things. I ran into problems left and right, but I was able to solve
them quickly enough by searching the internet. It took me a while to figure out how to do the sinusoidal fade, but that was mostly due to me thinking that
I could figure it out without looking anything up. After a lot of debugging, I [looked up](https://andrea-toscano.com/fading-led-with-sine-wave/) how to 
do a sinusoidal fade and reverse engineered from there, which, after a short period of head-scratching, brought me to the desired solution.

<br>
<br>

## Finite_LED_Blinker

### Description & Code

The goal of this project was to make an LED blink *5* times and then turn off, so naturally, I wanted to take this a step furthur. My project flips 
between two LEDs, fading them in and out sinusoidally 4 times with a randomly generated sine wave length. The code for the project built on the LED fade 
code by creating a new function which mostly took over the job of the main loop, and elaborating on the visualizeBrightness function.

##### Controlling the LED blinkCycle

```C++
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
```
This function takes an LED, a sine wave length, and a char to use for visualization, and makes the LED fade the specified amount of times while visualizing
the brightness of the LED. The way that the code checks if one wave has been completed is by checking if the full length of the wave has been reached.
Since the counter which controls the x-values starts at *-1/3* of the length of the wave, the if statement has to compensate for that, because it needs to 
be able to use the true counter value. 

##### Visualization of Brightness

```C++
void visualizeBrightness(int brightness, char visualizationChar) {
  brightness = brightness / 6;   //make brightness val smaller so the graph isn't huge
  for (int i = 0; i < brightness; i++) {    //print the specified char for every point of brightness
    Serial.print(visualizationChar);
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
```

The visualizeBrightness function is the same as [last time](#visualization-of-brightness), but it adds the ability to specify which char is used to graph 
the function.

### Evidence

[Code in Arduino Create](https://create.arduino.cc/editor/pschake34/3b0101d4-b6bf-4a6f-8f3f-6bbd19bd4be1)

[Project Folder](/finite_blink)

### Images

**The Wiring for Finite LED Blink**

<img src="/finite_blink/wiring/wiring.png" height=360px>

**Demo of Working Project**

<img src="/finite_blink/demo_video/demo.gif" height=360px>

### Reflection

This project was very satisfying to finish and watch it work. The only major problem that I ran into was with identifying where the end of one wave was. 
At first, I thought that I could just check for when a wave had reached *0* and advance the cycleCounter that way, but I found that if I got a very
large wave, there might be two *0*'s at the bottom of the wave, which would advance the cycleCounter twice, creating a problem. The second idea I had was
that I could just figure how long a wave was, and then recognize when a wave had been completed that way. This method was helped by the realization that 
my sineLength variable was also the amount of brightness values in one wave. However, this solution also posed its own problem -- when starting the 
counter for the x-values at *0*, the wave would start part of the way through. My solution to this problem, thankfully, was simple. I found that the wave 
would start exactly *1/3* of the way through, so I could just subtract *1/3* of the sineLength from the counter at the start of the loop.

<br>
<br>

# Arduino Review

### Description & Code

This assignment is just a review of some things that we learned last year in Engineering I. The assignment was broken into two parts - the first part (called 
Variable LED) was to make an LED blink with a delay of 1000ms, and make it blink faster by 100ms until the delay was only 100ms, at which point it would continue 
to blink but not get any faster. The second part of the assignment (called Button LED) was to do the same thing, but only let it blink when a button was pressed. 
Unfortunately, most of the class didn't have a button, so we improvised with [this circuit](#images-2). 

#### Variable Blink

In order to continue the trend, I diverged significantly from the original instructions for the project. Instead of simply continuing to blink with a 100ms 
delay forever, I made my LED go faster and slower. Once the delay reached 100ms, I would start adding 100ms until it reached 1000ms. However, I didn't stop 
there. Next, I added a second LED into the mix. Now the first LED would blink increasingly quickly, and blink back and forth with the second LED. The 
second LED would blink increasingly slowly, and then the two LED's would blink back and forth. This cycle was accomplished with two functions:

##### LED Cycle

```C++
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
```

The ledCycle function makes a specified LED blink increasingly quickly or increasingly slowly, as specified by the descending option. Basically, it adds 
the delay change to the delay variable until the delay variable reaches the limit, at which point it breaks the loop.

##### Transition

```C++
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
```
The transition function makes two LED's blink back and forth at a specified delay. The LED's blink back and forth 6 times and then stop. This function is 
used between the two LED cycles in the loop() to make the sequence seem more natural.

#### Button LED

In this part of the assignment, I stayed on track with the instructions more, but I still played around with it a bit. I only used one LED, which meant 
that most of the code I wrote for the previous half of the assignment was unnecessary. Therefore, I scrapped the two functions I had made, and put 
everything into the loop function.

##### Loop Function

```C++
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
```

As you can probably see, the basic concept is the same as the [LED Cycle](#led-cycle) function. I did add some new functionality, however, such as a period 
of fast blinking after the blink delay reaches 100ms, checking if the button is pressed every time through the loop, and printing helpful messages in the 
Serial monitor.

### Evidence

[Variable LED Code in Arduino Create](https://create.arduino.cc/editor/pschake34/c8e6787b-dd88-4ded-905f-08aeb58bcdb6/preview)

[Button LED Code in Arduino Create](https://create.arduino.cc/editor/pschake34/93297834-6397-4231-8a95-426bcd486201/preview)

[Project Folder](/arduino_review)

### Images

**The Wiring for Variable Blink**

<img src="/finite_blink/wiring/wiring.png" height=360px alt="Part 1 Wiring">

**The Wiring for Button LED**

<img src="/arduino_review/wiring/wiring.png" height=360px alt="Part 2 Wiring">

**Demo of Button LED**

<img src="/arduino_review/demo_video/demo.gif" height=360px alt="Part 2 Demo">

### Reflection

This project took longer than I was hoping, which was mostly due to me overdoing the first part of the assignment. Because I made the first part with two 
LED's, I couldn't reuse a lot of the code in the second part. In the future, I'm going to try to think about how I can plan for the next part of the 
assignment, and not overdo assignments while still having fun with them.
