# arduino-led-helmet
code for an arduino that controls WS2812B LED strips on a bicycle helmet

The code uses the FastLED library to control the LED strip, so it doesn't just support WS2812B strips, but any LED strip supported by FastLED should work.
I used an Arduino Pro Mini 5V , which gets powered by a USB power bank that also powers the LED strip. A small pushbutton between pin 3 and GND lets you switch between different light patterns.
