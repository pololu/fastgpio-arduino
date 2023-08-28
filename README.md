# FastGPIO library for Arduino

[www.pololu.com](https://www.pololu.com/)

## Summary

This is a C++ library for the Arduino IDE that allows you to manipulate general-purpose I/O (GPIO) pins on your Arduino or Arduino-compatible board with minimal overhead.  Many function calls to this library will be inlined and compiled down to just one or two assembly instructions.

This library is intended to be a replacement for the default Arduino I/O functions (`pinMode`, `digitalWrite`, and `digitalRead`) and has several advantages over them:

* The compiled code runs faster.
* Operates only on the specific bits used by the pin instead of doing read-write-modify operations on entire registers.
* Never disables interrupts.
* Supports reading and restoring the state of a pin, which is useful if the pin is used for multiple purposes.
* Pins can be specified either by their AVR pin name or their Arduino pin name.

To use this library, you will need a basic understanding of microcontroller I/O pins.  General information on this topic can be found in the Arduino [Digital Pins tutorial](https://arduino.cc/en/Tutorial/DigitalPins).

Currently, this library requires that the pin number you specify must be known at compile time.  This means the pin number cannot come from a variable that might change and it cannot be the result of a complicated calculation.  This allows the compiler to generate optimal code for manipulating that pin.

The Arduino GPIO functions automatically turn off a pin's PWM function when accessing it with `digitalRead` or `digitalWrite`.  This library does not have that feature.

## Supported platforms

This library is designed to work with the Arduino IDE versions 1.0.x, 1.5.x, 1.6.x, and later, and will probably not work with earlier versions.

This library currently supports any board based on these AVRs:

- ATmega48PB, ATmega88PB, ATmega168PB, ATmega328PB
- ATmega48, ATmega48P, ATmega88, ATmega88P, ATmega168, ATmega168P, ATmega328, ATmega328P
- ATmega16U4, ATmega32U4

## Getting started

### Software

If you are using version 1.6.2 or later of the
[Arduino software (IDE)](https://www.arduino.cc/en/Main/Software), you can use
the Library Manager to install this library:

1. In the Arduino IDE, open the "Sketch" menu, select "Include Library", then
   "Manage Libraries...".
2. Search for "FastGPIO".
3. Click the FastGPIO entry in the list.
4. Click "Install".

If this does not work, you can manually install the library:

1. Download the
   [latest release archive from GitHub](https://github.com/pololu/fastgpio-arduino/releases)
   and decompress it.
2. Rename the folder "fastgpio-arduino-xxxx" to "FastGPIO".
3. Drag the "FastGPIO" folder into the "libraries" directory inside your
   Arduino sketchbook directory. You can view your sketchbook location by
   opening the "File" menu and selecting "Preferences" in the Arduino IDE. If
   there is not already a "libraries" folder in that location, you should make
   the folder yourself.
4. After installing the library, restart the Arduino IDE.

## Specifying a pin

There are three ways to specify a pin:
* By its pin number
* By its AVR pin name, using the `IO_*` macros that this library provides.  For example, `IO_D3` refers to pin PD3.
* By alternative names defined in the Arduino IDE's `pins_arduino.h` header, such as `A2` and `MOSI`.
* By the special `IO_NONE` macro.  Commands operating on the `IO_NONE` pin will have no effect.

Any pin number that works with the standard Arduino I/O functions will work with the FastGPIO library.

For a full list of all the supported pins, see the "Pin number reference" section below.

## Digital outputs

This example shows how to set pin 13 as an output and drive it high:

~~~{.cpp}
FastGPIO::Pin<13>::setOutput(HIGH);
~~~

## Digital inputs

To configure a pin as a digital input with the internal pull-up resistor disabled, run:

~~~{.cpp}
FastGPIO::Pin<12>::setInput();
~~~

To configure a pin as a digital input with the internal pull-up resistor enabled, run:

~~~{.cpp}
FastGPIO::Pin<12>::setInputPulledUp();
~~~

Then, to read the value of the input, you can use:

~~~{.cpp}
bool inputHigh = FastGPIO::Pin<12>::isInputHigh();
~~~

## Pin number reference

### Pins for ATmega328PB boards

<table>
<tr><th>Number</th><th>AVR pin macro</th><th>Alternative name</th></tr>
<tr><td>0</td><td>IO_D0</td><td></td></tr>
<tr><td>1</td><td>IO_D1</td><td></td></tr>
<tr><td>2</td><td>IO_D2</td><td></td></tr>
<tr><td>3</td><td>IO_D3</td><td></td></tr>
<tr><td>4</td><td>IO_D4</td><td></td></tr>
<tr><td>5</td><td>IO_D5</td><td></td></tr>
<tr><td>6</td><td>IO_D6</td><td></td></tr>
<tr><td>7</td><td>IO_D7</td><td></td></tr>
<tr><td>8</td><td>IO_B0</td><td></td></tr>
<tr><td>9</td><td>IO_B1</td><td></td></tr>
<tr><td>10</td><td>IO_B2</td><td>SS</td></tr>
<tr><td>11</td><td>IO_B3</td><td>MOSI</td></tr>
<tr><td>12</td><td>IO_B4</td><td>MISO</td></tr>
<tr><td>13</td><td>IO_B5</td><td>SCK</td></tr>
<tr><td>14</td><td>IO_C0</td><td>A0</td></tr>
<tr><td>15</td><td>IO_C1</td><td>A1</td></tr>
<tr><td>16</td><td>IO_C2</td><td>A2</td></tr>
<tr><td>17</td><td>IO_C3</td><td>A3</td></tr>
<tr><td>18</td><td>IO_C4</td><td>A4, SDA, SDA0</td></tr>
<tr><td>19</td><td>IO_C5</td><td>A5, SCL, SCL0</td></tr>
<tr><td>20</td><td>IO_E2</td><td>A6</td></tr>
<tr><td>21</td><td>IO_E3</td><td>A7</td></tr>
<tr><td>22</td><td>IO_E0</td><td>SDA1</td>
<tr><td>23</td><td>IO_E1</td><td>SCL1</td>
<tr><td>24</td><td>IO_C6</td><td></td></tr>
</table>


### Pins for ATmega328P boards

<table>
<tr><th>Number</th><th>AVR pin macro</th><th>Alternative name</th></tr>
<tr><td>0</td><td>IO_D0</td><td></td></tr>
<tr><td>1</td><td>IO_D1</td><td></td></tr>
<tr><td>2</td><td>IO_D2</td><td></td></tr>
<tr><td>3</td><td>IO_D3</td><td></td></tr>
<tr><td>4</td><td>IO_D4</td><td></td></tr>
<tr><td>5</td><td>IO_D5</td><td></td></tr>
<tr><td>6</td><td>IO_D6</td><td></td></tr>
<tr><td>7</td><td>IO_D7</td><td></td></tr>
<tr><td>8</td><td>IO_B0</td><td></td></tr>
<tr><td>9</td><td>IO_B1</td><td></td></tr>
<tr><td>10</td><td>IO_B2</td><td>SS</td></tr>
<tr><td>11</td><td>IO_B3</td><td>MOSI</td></tr>
<tr><td>12</td><td>IO_B4</td><td>MISO</td></tr>
<tr><td>13</td><td>IO_B5</td><td>SCK</td></tr>
<tr><td>14</td><td>IO_C0</td><td>A0</td></tr>
<tr><td>15</td><td>IO_C1</td><td>A1</td></tr>
<tr><td>16</td><td>IO_C2</td><td>A2</td></tr>
<tr><td>17</td><td>IO_C3</td><td>A3</td></tr>
<tr><td>18</td><td>IO_C4</td><td>A4, SDA</td></tr>
<tr><td>19</td><td>IO_C5</td><td>A5, SCL</td></tr>
<tr><td>20</td><td>IO_C6</td><td></td></tr>
</table>

### Pins for ATmega32U4 boards

<table>
<tr><th>Number</th><th>AVR pin macro</th><th>Alternative name</th></tr>
<tr><td>0</td><td>IO_D2</td><td></td></tr>
<tr><td>1</td><td>IO_D3</td><td></td></tr>
<tr><td>2</td><td>IO_D1</td><td>SDA</td></tr>
<tr><td>3</td><td>IO_D0</td><td>SCL</td></tr>
<tr><td>4, 24</td><td>IO_D4</td><td>A6</td></tr>
<tr><td>5</td><td>IO_C6</td><td></td></tr>
<tr><td>6, 25</td><td>IO_D7</td><td>A7</td></tr>
<tr><td>7</td><td>IO_E6</td><td></td></tr>
<tr><td>8, 26</td><td>IO_B4</td><td>A8</td></tr>
<tr><td>9, 27</td><td>IO_B5</td><td>A9</td></tr>
<tr><td>10, 28</td><td>IO_B6</td><td>A10</td></tr>
<tr><td>11</td><td>IO_B7</td><td></td></tr>
<tr><td>12, 29</td><td>IO_D6</td><td>A11</td></tr>
<tr><td>13</td><td>IO_C7</td><td></td></tr>
<tr><td>14</td><td>IO_B3</td><td>MISO</td></tr>
<tr><td>15</td><td>IO_B1</td><td>SCK</td></tr>
<tr><td>16</td><td>IO_B2</td><td>MOSI</td></tr>
<tr><td>17</td><td>IO_B0</td><td>SS</td></tr>
<tr><td>18</td><td>IO_F7</td><td>A0</td></tr>
<tr><td>19</td><td>IO_F6</td><td>A1</td></tr>
<tr><td>20</td><td>IO_F5</td><td>A2</td></tr>
<tr><td>21</td><td>IO_F4</td><td>A3</td></tr>
<tr><td>22</td><td>IO_F1</td><td>A4</td></tr>
<tr><td>23</td><td>IO_F0</td><td>A5</td></tr>
<tr><td>30</td><td>IO_D5</td><td></td></tr>
<tr><td>31</td><td>IO_E2</td><td></td></tr>
</table>

## Speed test

We compiled the following code with the Arduino IDE 1.5.8 and ran it on an ATmega32U4 running at 16 MHz:

~~~{.cpp}
#include <FastGPIO.h>
#include <util/delay.h>

void setup() {
  FastGPIO::Pin<A1>::setOutputLow();
}

void loop() {
  FastGPIO::Pin<A1>::setOutputValueHigh();
  FastGPIO::Pin<A1>::setOutputValueLow();
  _delay_us(10);
  digitalWrite(A1, HIGH);
  digitalWrite(A1, LOW);
  _delay_us(10);
}
~~~

The pulses generated by the FastGPIO calls were 0.125&nbsp;&mu;s long because each call was compiled to just a single assembly instruction, while the pulses generated by `digitalWrite` were 5.1&nbsp;&mu;s long.

## Error messages

If you specify an invalid pin number, GCC will produce error messages like this:

~~~
warning: array subscript is above array bounds
warning: asm operand 0 probably doesn't match constraints
error: impossible constraint in 'asm'
~~~

This is because the pin number is checked at compile time and must be valid.

## Classes

The classes provided by this library are listed below:

* FastGPIO::Pin
* FastGPIO::PinLoan

## Documentation

For complete documentation, see https://pololu.github.io/fastgpio-arduino.
If you are already on that page, then click on the links in the "Classes" section above.

## Version history

* 2.2.0 (2023-08-28): Added support for some chips with the same pinout as already-supported chips:
  ATmega48PB, ATmega88PB, ATmega168PB, ATmega48, ATmega48P, ATmega88, ATmega88P, ATmega16U4.
* 2.1.0 (2018-02-27): Added support for the ATmega328PB.
* 2.0.0 (2016-08-19): Updated library to work with the Arduino Library Manager.
* 1.0.2 (2015-03-16): Improved the speed of toggling a pin's output value.
* 1.0.1 (2015-01-06): Introduced some casts to fix compiler warnings.
* 1.0.0 (2014-12-11): Original release.
