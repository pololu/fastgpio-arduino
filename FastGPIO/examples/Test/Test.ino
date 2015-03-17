/* This test code is not meant to be run on real hardware.
It can be compiled and then disassembled in order to ensure that
the FastGPIO library produces efficient assembly.

To disassemble, find the Arduino build directory and run:
avr-objdump -D *.elf > ~/disasm.txt

The desired assembly listed here assumes you are compiling for an
ATmega32U4; if you are using a different chip then the register and
bit numbers will be different but the instruction opcodes should
still be the same.
*/

#include <FastGPIO.h>

bool x;

/*
Desired assembly:
  cbi   0x0b, 3
  sbi   0x0a, 3
*/
void testOutputLow() __attribute__((noinline));
void testOutputLow()
{
    FastGPIO::Pin<1>::setOutputLow();
}

/*
Desired assembly:
  sbi   0x0b, 3
  sbi   0x0a, 3
*/
void testOutputHigh() __attribute__((noinline));
void testOutputHigh()
{
    FastGPIO::Pin<1>::setOutputHigh();
}

/* Desired assembly:
  sbi   0x09, 3
  sbi   0x0a, 3
*/
void testOutputToggle() __attribute__((noinline));
void testOutputToggle()
{
    FastGPIO::Pin<1>::setOutputToggle();
}

/*
Desired assembly:
  cbi  0x0b, 3
  sbi  0x0a, 3
  sbi  0x0b, 3
  sbi  0x0a, 3
  lds  r24, x
  and  r24, r24
  breq .+4
  sbi  0x0b
  rjmp .+2
  cbi  0x0b, 3
  sbi  0x0a, 3
*/
void testOutput() __attribute__((noinline));
void testOutput()
{
    FastGPIO::Pin<1>::setOutput(0);
    FastGPIO::Pin<1>::setOutput(1);
    FastGPIO::Pin<1>::setOutput(x);
}

/*
Desired assembly:
  cbi  0x0b, 3
*/
void testOutputValueLow() __attribute__((noinline));
void testOutputValueLow()
{
    FastGPIO::Pin<1>::setOutputValueLow();
}

/*
Desired assembly:
  sbi  0x0b, 3
*/
void testOutputValueHigh() __attribute__((noinline));
void testOutputValueHigh()
{
    FastGPIO::Pin<1>::setOutputValueHigh();
}

/*
Desired assembly:
  sbi   0x09, 3
*/
void testOutputValueToggle() __attribute__((noinline));
void testOutputValueToggle()
{
    FastGPIO::Pin<1>::setOutputValueToggle();
}

/*
Desired assembly:
  cbi 0x0b, 3
  sbi 0x0b, 3
  lds r24, 0x0128
  and r24, r24
  breq .+4
  sbi 0x0b, 3
  ret
  cbi 0x0b, 3
  ret
*/
void testOutputValue() __attribute__((noinline));
void testOutputValue()
{
    FastGPIO::Pin<1>::setOutputValue(0);
    FastGPIO::Pin<1>::setOutputValue(1);
    FastGPIO::Pin<1>::setOutputValue(x);
}

/*
Desired assembly:
  cbi 0x0a, 3
  cbi 0x0b, 3
*/
void testSetInput() __attribute__((noinline));
void testSetInput()
{
    FastGPIO::Pin<1>::setInput();
}

/*
Desired assembly:
  cbi 0x0a, 3
  sbi 0x0b, 3
*/
void testSetInputWithPullup() __attribute__((noinline));
void testSetInputWithPullup()
{
    FastGPIO::Pin<1>::setInputPulledUp();
}

/*
Desired assembly:
  sbis 0x09, 3
  rjmp .+6
  ...
*/
void testIsInputHigh() __attribute__((noinline));
void testIsInputHigh()
{
    if (FastGPIO::Pin<1>::isInputHigh())
    {
       PIND = 0x44;
    }
    else
    {
       PINC = 0x55;
    }
}

/*
Desired assembly:
  ldi r18, 0
  sbic 0x0b, 3
  ori r18, 1
  sbic 0x0a, 3
  ori r18, 0x02
  nop
  bst r18, 1
  brts .+2
  cbi 0x0a, 3
  bst r18, 0
  brts .+2
  cbi 0x0b, 3
  brtc .+2
  sbi 0x0b, 3
  bst r18, 1
  brtc .+2
  sbi 0x0a, 3
  ret
 */
void testGetAndSetState() __attribute__((noinline));
void testGetAndSetState()
{
    uint8_t pin1State = FastGPIO::Pin<1>::getState();
    asm volatile("nop\n");
    FastGPIO::Pin<1>::setState(pin1State);
}

/*
Desired assembly:  Just like testGetAndSetState, but on a different pin.
Using the PinLoan class does not introduce overhead.
*/
void testPinLoan() __attribute__((noinline));
void testPinLoan()
{
    FastGPIO::PinLoan<2> loan1;
    asm volatile("nop\n");
}

void setup()
{
  testOutputLow();
  testOutputHigh();
  testOutputToggle();
  testOutput();
  testOutputValueLow();
  testOutputValueHigh();
  testOutputValueToggle();
  testOutputValue();
  testSetInput();
  testSetInputWithPullup();
  testIsInputHigh();
  testGetAndSetState();
  testPinLoan();
}

void loop()
{
}
