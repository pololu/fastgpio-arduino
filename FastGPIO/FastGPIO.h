/* FastGPIO - C++ header library for efficient AVR I/O
Copyright (C) 2014 Pololu Corporation - see LICENSE.txt for details
Origin: https://github.com/pololu/fastgpio-arduino
*/

#pragma once
#include <avr/io.h>
#include <stdint.h>

#define _FG_SBI(mem_addr, bit) asm volatile("sbi %0, %1\n" : \
    : "I" (mem_addr - __SFR_OFFSET), "I" (bit))
#define _FG_CBI(mem_addr, bit) asm volatile("cbi %0, %1\n" : \
    : "I" (mem_addr - __SFR_OFFSET), "I" (bit))

namespace FastGPIO
{
    typedef struct IOStruct
    {
        uint8_t pinAddr;
        uint8_t portAddr;
        uint8_t ddrAddr;
        uint8_t bit;

        volatile uint8_t * pin() const
        {
            return (volatile uint8_t *)pinAddr;
        }

        volatile uint8_t * port() const
        {
            return (volatile uint8_t *)portAddr;
        }

        volatile uint8_t * ddr() const
        {
            return (volatile uint8_t *)ddrAddr;
        }
    } IOStruct;

#define _FG_PIN(port, bit) { _SFR_MEM_ADDR(PIN##port), _SFR_MEM_ADDR(PORT##port), \
     _SFR_MEM_ADDR(DDR##port), bit }

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega168P) || defined(__AVR_ATmega328) || defined(__AVR_ATmega328P__)

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
#define IO_D4 24
#define IO_D7 25
#define IO_B4 26
#define IO_B5 27
#define IO_B6 28
#define IO_D6 29
#define IO_D5 30
#define IO_E2 31
#define IO_NONE 32

#else
#error FastGPIO does not support this board.
#endif

    template<uint8_t pin> class Pin
    {
    public:
        static inline void setOutputLow() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        static inline void setOutputHigh() __attribute__((always_inline))
        {
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        static inline void setOutputToggle() __attribute__((always_inline))
        {
            setOutputValueToggle();
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        static inline void setOutput(bool value) __attribute__((always_inline))
        {
            setOutputValue(value);
            _FG_SBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
        }

        static inline void setOutputValueLow() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        static inline void setOutputValueHigh() __attribute__((always_inline))
        {
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        static inline void setOutputValueToggle() __attribute__((always_inline))
        {
            asm volatile(
                "sbic %1, %0\n"
                "rjmp .+4\n"
                "sbi  %1, %0\n"
                "rjmp .+2\n"
                "cbi  %1, %0\n"
                :
                : "I" (pinStructs[pin].bit),
                  "I" (pinStructs[pin].portAddr - __SFR_OFFSET));
        }

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

        static inline void setInput() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
            _FG_CBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        static inline void setInputPulledUp() __attribute__((always_inline))
        {
            _FG_CBI(pinStructs[pin].ddrAddr, pinStructs[pin].bit);
            _FG_SBI(pinStructs[pin].portAddr, pinStructs[pin].bit);
        }

        static inline bool isInputHigh() __attribute__((always_inline))
        {
            return *pinStructs[pin].pin() >> pinStructs[pin].bit & 1;

            /** This is another option but it is sometimes less efficient:
            bool value;
            asm volatile(
                "ldi %0, 0\n"
                "sbic %2, %1\n"
                "ldi %0, 1\n"
                : "=d" (value)
                : "I" (pinStructs[pin].bit),
                  "I" (pinStructs[pin].pinAddr - __SFR_OFFSET));
            return value;
            **/
        }

        static inline bool isOutput() __attribute__((always_inline))
        {
            return *pinStructs[pin].ddr() >> pinStructs[pin].bit & 1;
        }

        static inline bool getOutputValue() __attribute__((always_inline))
        {
            return *pinStructs[pin].port() >> pinStructs[pin].bit & 1;
        }

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

            /** Equivalent C++ code:
              return isOutput() << 1 | getOutputValue();
            **/
        }

        static void setState(uint8_t state)
        {
            // Sometimes both the PORT bit and the DDR bit will need
            // to change, so we should think carefully about what
            // order we set them.  Our plan is that if DDR is getting set to 0,
            // we will do that first, and if it is getting set to 1, we will do that
            // last.  This guarantees that the intermediate state is always in input.
            //
            // This table shows the possible transitions if both bits are changing:
            //
            // Current State    |  Intermediate State  |  Final State
            // Output low       |  Input               |  Input pulled up
            // Output high      |  Input pulled up     |  Input
            // Input            |  Input pulled up     |  Output high
            // Input pulled up  |  Input               |  Output low

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

    template<uint8_t pin> class PinLoan
    {
    public:
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
