// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

/*! \file FastGPIO.h

FastGPIO is a C++ header library for efficient AVR I/O.

For an overview of the features of this library, see
https://github.com/pololu/fastgpio-arduino.
That is the main repository for this library, though copies may exist in other
repositories.

The FastGPIO::Pin class provides static functions for manipulating pins.  See
its class reference for more information.

\class FastGPIO::Pin

@tparam pin The pin number

The FastGPIO::Pin class provides static functions for manipulating pins.  This
class can only be used if the pin number is known at compile time, which means
it does not come from a variable that might change and it does not come from the
result of a complicated calculation.

Here is some example code showing how to use this class to blink an LED:

~~~{.cpp}
#include <FastGPIO.h>

#define LED_PIN 13

void setup() {
}

void loop() {
  FastGPIO::Pin<LED_PIN>::setOutput(0);
  delay(500);
  FastGPIO::Pin<LED_PIN>::setOutput(1);
  delay(500);
}
~~~

*/

#pragma once
#include <avr/io.h>
#include <stdint.h>

/** @cond */
#define _FG_SBI(mem_addr, bit) asm volatile("sbi %0, %1\n" : \
    : "I" (mem_addr - __SFR_OFFSET), "I" (bit))
#define _FG_CBI(mem_addr, bit) asm volatile("cbi %0, %1\n" : \
    : "I" (mem_addr - __SFR_OFFSET), "I" (bit))
#define _FG_PIN(port, bit) { _SFR_MEM_ADDR(PIN##port), _SFR_MEM_ADDR(PORT##port), \
     _SFR_MEM_ADDR(DDR##port), bit }
/** @endcond */

namespace FastGPIO
{
    /** @cond */
    /** The IOStruct struct and the pinStructs array below are not documented in
     * the Doxygen documentation, but can be used by advanced users of this
     * library and are considered to be part of the public API for the purposes
     * of semantic versioning.
     */
    typedef struct IOStruct
    {
        uint8_t pinAddr;
        uint8_t portAddr;
        uint8_t ddrAddr;
        uint8_t bit;

        volatile uint8_t * pin() const
        {
            return (volatile uint8_t *)(uint16_t)pinAddr;
        }

        volatile uint8_t * port() const
        {
            return (volatile uint8_t *)(uint16_t)portAddr;
        }

        volatile uint8_t * ddr() const
        {
            return (volatile uint8_t *)(uint16_t)ddrAddr;
        }
    } IOStruct;
    /** @endcond */

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)

    const IOStruct pinStructs[] = {
        _FG_PIN(D, 0),
        _FG_PIN(D, 1),
        _FG_PIN(D, 2),
        _FG_PIN(D, 3),
        _FG_PIN(D, 4),
        _FG_PIN(D, 5),
        _FG_PIN(D, 6),
        _FG_PIN(D, 7),
        _FG_PIN(B, 0),
        _FG_PIN(B, 1),
        _FG_PIN(B, 2),
        _FG_PIN(B, 3),
        _FG_PIN(B, 4),
        _FG_PIN(B, 5),
        _FG_PIN(C, 0),
        _FG_PIN(C, 1),
        _FG_PIN(C, 2),
        _FG_PIN(C, 3),
        _FG_PIN(C, 4),
        _FG_PIN(C, 5),
        _FG_PIN(C, 6),
        _FG_PIN(C, 7), // Null pin (IO_NONE)
    };

#define IO_D0 0
#define IO_D1 1
#define IO_D2 2
#define IO_D3 3
#define IO_D4 4
#define IO_D5 5
#define IO_D6 6
#define IO_D7 7
#define IO_B0 8
#define IO_B1 9
#define IO_B2 10
#define IO_B3 11
#define IO_B4 12
#define IO_B5 13
#define IO_C0 14
#define IO_C1 15
#define IO_C2 16
#define IO_C3 17
#define IO_C4 18
#define IO_C5 19
#define IO_C6 20
#define IO_NONE 21

#elif defined(__AVR_ATmega32U4__)

    const IOStruct pinStructs[] = {
        _FG_PIN(D, 2),
        _FG_PIN(D, 3),
        _FG_PIN(D, 1),
        _FG_PIN(D, 0),
        _FG_PIN(D, 4),
        _FG_PIN(C, 6),
        _FG_PIN(D, 7),
        _FG_PIN(E, 6),

        _FG_PIN(B, 4),
        _FG_PIN(B, 5),
        _FG_PIN(B, 6),
        _FG_PIN(B, 7),
        _FG_PIN(D, 6),
        _FG_PIN(C, 7),

        _FG_PIN(B, 3),
        _FG_PIN(B, 1),
        _FG_PIN(B, 2),
        _FG_PIN(B, 0),

        _FG_PIN(F, 7),
        _FG_PIN(F, 6),
        _FG_PIN(F, 5),
        _FG_PIN(F, 4),
        _FG_PIN(F, 1),
        _FG_PIN(F, 0),

        _FG_PIN(D, 4),
        _FG_PIN(D, 7),
        _FG_PIN(B, 4),
        _FG_PIN(B, 5),
        _FG_PIN(B, 6),
        _FG_PIN(D, 6),

        // Extra pins added by this library and not supported by the
        // Arduino GPIO functions:
        _FG_PIN(D, 5),
        _FG_PIN(E, 2),

        _FG_PIN(E, 0)  // Null pin (IO_NONE)
    };

#define IO_D2 0
#define IO_D3 1
#define IO_D1 2
#define IO_D0 3
#define IO_D4 4
#define IO_C6 5
#define IO_D7 6
#define IO_E6 7
#define IO_B4 8
#define IO_B5 9
#define IO_B6 10
#define IO_B7 11
#define IO_D6 12
#define IO_C7 13
#define IO_B3 14
#define IO_B1 15
#define IO_B2 16
#define IO_B0 17
#define IO_F7 18
#define IO_F6 19
#define IO_F5 20
#define IO_F4 21
#define IO_F1 22
#define IO_F0 23
#define IO_D5 30
#define IO_E2 31
#define IO_NONE 32

#else
#error FastGPIO does not support this board.
#endif

    template<uint8_t pin> class Pin
    {
    public:
        /*! \brief Configures the pin to be an output driving low.
         *
         * This is equivalent to calling setOutput with an argument of 0,
         * but it has a simpler implementation which means it is more
         * likely to be compiled down to just 2 assembly instructions.
         */
        static inline void setOutputLow() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        /*! \brief Configures the pin to be an output driving high.
         *
         * This is equivalent to calling setOutput with an argument of 1,
         * but it has a simpler implementation which means it is more
         * likely to be compiled down to just 2 assembly instructions.
         */
        static inline void setOutputHigh() __attribute__((always_inline))
        {
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        /*! \brief Configures the pin to be an output and toggles it.
         */
        static inline void setOutputToggle() __attribute__((always_inline))
        {
            setOutputValueToggle();
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        /*! \brief Sets the pin as an output.
         *
         * @param value Should be 0, LOW, or false to drive the pin low.  Should
         * be 1, HIGH, or true to drive the pin high.
         *
         * The PORT bit is set before the DDR bit to ensure that the output is
         * not accidentally driven to the wrong value during the transition.
         */
        static inline void setOutput(bool value) __attribute__((always_inline))
        {
            setOutputValue(value);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        /*! \brief Sets the output value of the pin to 0.
         *
         * This is mainly intended to be used on pins that have already been
         * configured as an output in order to make the output drive low.
         *
         * If this is used on an input pin, it has the effect of disabling the
         * input pin's pull-up resistor.
         */
        static inline void setOutputValueLow() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        /*! \brief Sets the output value of the pin to 1.
         *
         * This is mainly intended to be used on pins that have already been
         * configured as an output in order to make the output drive low.
         *
         * If this is used on an input pin, it has the effect of enabling the
         * input pin's pull-up resistor.
         */
        static inline void setOutputValueHigh() __attribute__((always_inline))
        {
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        /*! \brief Toggles the output value of the pin.
         *
         * This is mainly intended to be used on pins that have already been
         * configured as an output.  If the pin was driving low, this function
         * changes it to drive high.  If the pin was driving high, this function
         * changes it to drive low.
         *
         * If this function is used on an input pin, it has the effect of
         * toggling the state of the input pin's pull-up resistor.
         */
        static inline void setOutputValueToggle() __attribute__((always_inline))
        {
            _FG_SBI(pinStructs[pin].pinAddr, pinStructs[pin].bit);
        }

        /*! \brief Sets the output value of the pin.
         *
         * @param value Should be 0, LOW, or false to drive the pin low.  Should
         * be 1, HIGH, or true to drive the pin high.
         *
         * This is mainly intended to be used on pins that have already been
         * configured as an output.
         *
         * If this function is used on an input pin, it has the effect of
         * toggling setting the state of the input pin's pull-up resistor.
         */
        static inline void setOutputValue(bool value) __attribute__((always_inline))
        {
            if (value)
            {
                _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            }
            else
            {
                _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            }
        }

        /*! \brief Sets a pin to be a digital input with the internal pull-up
         *  resistor disabled.
         */
        static inline void setInput() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        /*! \brief Sets a pin to be a digital input with the internal pull-up
         *  resistor enabled.
         */
        static inline void setInputPulledUp() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        /*! \brief Reads the input value of the pin.
         *
         * @return 0 if the pin is low, 1 if the pin is high.
         */
        static inline bool isInputHigh() __attribute__((always_inline))
        {
            return *pinStructs[pin].pin() >> pinStructs[pin].bit & 1;

            /* This is another option but it is less efficient in code
               like "if (isInputHigh()) { ... }":
            bool value;
            asm volatile(
                "ldi %0, 0\n"
                "sbic %2, %1\n"
                "ldi %0, 1\n"
                : "=d" (value)
                : "I" (pinStructs[pin].bit),
                  "I" (pinStructs[pin].pinAddr - __SFR_OFFSET));
            return value;
            */
        }

        /*! \brief Returns 1 if the pin is configured as an output.
         *
         * @return 1 if the pin is an output, 0 if it is an input.
         */
        static inline bool isOutput() __attribute__((always_inline))
        {
            return *pinStructs[pin].ddr() >> pinStructs[pin].bit & 1;
        }

        /*! \brief Returns the output value of the pin.
         *
         * This is mainly intended to be called on pins that have been
         * configured an an output.  If it is called on an input pin, the return
         * value indicates whether the pull-up resistor is enabled or not.
         */
        static inline bool isOutputValueHigh() __attribute__((always_inline))
        {
            return *pinStructs[pin].port() >> pinStructs[pin].bit & 1;
        }

        /*! \brief Returns the full 2-bit state of the pin.
         *
         * Bit 0 of this function's return value is the pin's output value.
         * Bit 1 of the return value is the pin direction; a value of 1
         * means output.  All the other bits are zero.
         */
        static uint8_t getState()
        {
            uint8_t state;
            asm volatile(
                "ldi  %0, 0\n"
                "sbic %2, %1\n"
                "ori  %0, 1\n"   // Set state bit 0 to 1 if PORT bit is set.
                "sbic %3, %1\n"
                "ori  %0, 2\n"   // Set state bit 1 to 1 if DDR bit is set.
                : "=a" (state)
                : "I" (pinStructs[pin].bit),
                  "I" (pinStructs[pin].portAddr - __SFR_OFFSET),
                  "I" (pinStructs[pin].ddrAddr - __SFR_OFFSET));
            return state;

            /* Equivalent C++ code:
              return isOutput() << 1 | isOutputValueHigh();
            */
        }

        /*! \brief Sets the full 2-bit state of the pin.
         *
         * @param state The state of the pin, as returns from getState.
         * All bits other than bits 0 and 1 are ignored.
         *
         * Sometimes this function will need to change both the PORT bit (which
         * specifies the output value) and the DDR bit (which specifies whether
         * the pin is an output).  If the DDR bit is getting set to 0, this
         * function changes DDR first, and if it is getting set to 1, this
         * function changes DDR last.  This guarantees that the intermediate pin
         * state is always an input state.
         */
        static void setState(uint8_t state)
        {
            asm volatile(
                "bst  %0, 1\n"   // Set DDR to 0 if needed
                "brts .+2\n"
                "cbi  %3, %1\n"
                "bst  %0, 0\n"   // Copy state bit 0 to PORT bit
                "brts .+2\n"
                "cbi  %2, %1\n"
                "brtc .+2\n"
                "sbi  %2, %1\n"
                "bst  %0, 1\n"   // Set DDR to 1 if needed
                "brtc .+2\n"
                "sbi  %3, %1\n"
                :
                : "a" (state),
                  "I" (pinStructs[pin].bit),
                  "I" (pinStructs[pin].portAddr - __SFR_OFFSET),
                  "I" (pinStructs[pin].ddrAddr - __SFR_OFFSET));
        }
    };

    /*! This class saves the state of the specified pin in its constructor when
     * it is created, and restores the pin to that state in its destructor.
     * This can be very useful if a pin is being used for multiple purposes.
     * It allows you to write code that temporarily changes the state of the
     * pin and is guaranteed to restore the state later.
     *
     * For example, if you were controlling both a button and an LED using a
     * single pin and you wanted to see if the button was pressed without
     * affecting the LED, you could write:
     *
     * ~~~{.cpp}
     * bool buttonIsPressed()
     * {
     *     FastGPIO::PinLoan<IO_D5> loan;
     *     FastGPIO::Pin<IO_D5>::setInputPulledUp();
     *     _delay_us(10);
     *     return !FastGPIO::Pin<IO_D5>::isInputHigh();
     * }
     * ~~~
     *
     * This is equivalent to:
     *
     * ~~~{.cpp}
     * bool buttonIsPressed()
     * {
     *     uint8_t state = FastGPIO::Pin<IO_D5>::getState();
     *     FastGPIO::Pin<IO_D5>::setInputPulledUp();
     *     _delay_us(10);
     *     bool value = !FastGPIO::Pin<IO_D5>::isInputHigh();
     *     FastGPIO::Pin<IO_D5>::setState(state);
     *     return value;
     * }
     * ~~~
     */
    template<uint8_t pin> class PinLoan
    {
    public:
        /*! \brief The state of the pin as returned from FastGPIO::Pin::getState. */
        uint8_t state;

        PinLoan()
        {
            state = Pin<pin>::getState();
        }

        ~PinLoan()
        {
            Pin<pin>::setState(state);
        }
    };
};

#undef _FG_PIN
#undef _FG_CBI
#undef _FG_SBI
