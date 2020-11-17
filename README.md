# NotSoBasicArduino

This repository includes all of my projects from NotSoBasicArduino. Each project has its own folder, which contains project files, circuit diagrams, and a
backup of the code, just in case Arduino Create goes away.

## Table of Contents

* [LED_Fade](#LED_Fade)
* [Hello_LCD](#Hello_LCD)
* [FillMeInLAter](#FillMeInLAter)

<br>
<br>

## LED_Fade

### Description & Code

The LED fades in and out sinusoidally, and visualizes its brightness in the serial monitor. My code 
contains two main functions: one which controls the variation of the brightness, and another which
visualizes the brightness in the serial monitor.

##### Variation of brightness:

```C++
void loop() {
  analogWrite(ledPin, brightness);   //set the LED brightness
  counter++;    //advance the counter
  brightness = offset + amplitude * sin((TWO_PI / length) * counter);   //change brightness for next loop
  visualizeBrightness(brightness);    //visualizes the brightness in the Serial monitor
  delay(150);   //adds delay so the fade happens gradually
}
```

Basically, counter goes up by one every time through the loop. The counter is then fed into the sine 
function as the x-value. **offset** and **amplitude** are constants which have been set up to 
constrain the sine wave to the proper values. **length** controls the size of the sine wave -- smaller 
values make the wave smaller and vise versa.

##### Visualization of brightness:

```C++
void visualizeBrightness(int brightness) {
  brightness = brightness / 6;   //make brightness val smaller
  for (int i = 0; i < brightness; i++) {    //print "=" for every point of brightness
    Serial.print("=");
  }
  Serial.println(">");    //makes the graph look slightly better and creates a newline
}
```

The brightness is divided by 6 so that the graph isn't quite so large, then a for loop prints "=" for each point of brightness. At the end, it prints "<",
which also creates a newline so that the next brightness visualization will be a line lower.

### Evidence

[Code in Arduino Create](https://create.arduino.cc/editor/pschake34/4d8e394c-59cf-47a7-9e31-5b1134052651)

### Images

<img src="/led_fade/wiring.png" height=360px alt="LED Fade Wiring">

**The Wiring for LED Fade**

<br>

<img src="/led_fade/demo.gif" height=360px alt="LED Fade Demo">

**Demonstration of working project**

### Reflection

This being the first code project, it took me a bit of time to get back in the swing of things. I ran into problems left and right, but I was able to solve
them quickly enough by searching the internet. It took me a while to figure out how to do the sinusoidal fade, but that was mostly due to me thinking that
I could figure it out with only minimal searching. After a lot of debugging, I looked up how to do it and reverse engineered from there, which, after a
short period of head-scratching, brought me to the desired solution.

<br>
<br>

## Hello_LCD

### Description & Code
Description goes here

Here's how you make code look like code:

```C++
Code goes here
```
Talk about how the code works, here....

### Evidence
link goes here

### Images
draw it yourself, take a picture, make a fritzing, whatever you want to EFFECTIVELY communicate how its put together.

### Reflection

