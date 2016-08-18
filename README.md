Helpful Pomodoro Chair Device
==========

Code for Arduino device that automatically times Pomodoro shifts and breaks.


This code has been written for an Arduino device that monitors how long I have been sitting in my work chair (via an infrared sensor) and makes me take breaks accordingly. It is written to roughly emulate Pomodoro-style breaks, timing a 24 minute work shift, followed by a three minute "limbo" phase to finish any work that I'm right in the middle of doing, followed by a five minute break. The beginning and end of a break is signaled by a buzzer playing particular sounds or brief musical riffs that I have borrowed shamelessly from Final Fantasy VII.

This is my first time ever writing in C++, so bear with the absurd abundance of unencapsulated methods for the moment — it seemed like an easier way to start than jumping directly into C++ objects.

Supplies needed:

- [Arduino](https://www.sparkfun.com/products/11021)
- 2 [switches](https://www.sparkfun.com/products/102)
- 1 [speaker](https://www.sparkfun.com/products/11089)
- 1 [multicolor led](https://www.sparkfun.com/products/11120)
- 1 [yellow led](https://www.sparkfun.com/products/9594)
- 1 [proximity sensor](https://www.amazon.com/Geeetech-Infrared-proximity-compatible-Arduino/dp/B00AMC1V2C)
- assorted resistors, wires, breadboard
 