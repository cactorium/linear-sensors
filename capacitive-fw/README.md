# Firmware for the capacitive sensor board
This is probably not the cleanest directory structure ever, but it works.
The firmware developed here is meant to be programmed onto the STM32F07 chip on the capacitive board.
This provides UART output on the J102 header at 115200 baud (adjustable in the source code) of the current position, output as a 64 bit hexadecimal, followed by a space and 64 zeros (TODO remove extra output).

The project is currently using `libopencm3` to avoid needing to read through the STM32F07 reference manual, and the OpenOCD config is for the FT232H chip. TODO provide more info about SWD programming with Adafruit's FT232H breakout
Any SWD-capable OpenOCD-compatible programmer should work.
You'll need the `arm-none-eabi-gcc` toolchain to build the project, although I'll probably add the final binaries to this repository at some point.

## How it works (TLDR)
Basically the position is approximately linear with respect to the detected phase of the signal, so the MCU needs to clean up the signal and find its phase to find its position.

## Internals
Most of the processing is done in the main loop, with interrupts providing the timing for the ADC conversion and square waves.
The system tick interrupt provides the timing for the entire system; it starts ADC conversions and toggles GPIO for the square waves.
The ADC interrupts stores the samples into a buffer, where it'll be slowly processed by the main loop.
Due to the limitations in processing speed, the ADC doesn't run continuously.
Instead, the ADC runs for the first N cycles of the square waves, enough to fill the buffer, with the ADC turned off for the remaining portion of the time. (maybe this is leading to more noise? TODO experiment with changing timing)
The number of ADC cycles and total cycles are easily adjusted to allow experimentation to try to improve latency or improve performance.
There's an overrun detector that'll output an 'o' onto the UART line whenever the main loop is taking too long to process the data.

The main loop passes the ADC samples into a cascade of three FIR filters, to reduce a lot of the mains noise and harmonics in the signal.
This is then multiplied with a 1 kHz cosine and 1 kHz sine wave to produce I (in phase) and Q (quadrature) components, which are summed over the entire sampling period.
This is then fed into an arctangent function based on CORDIC (Volder's algorithm) to produce this final phase information.

A lot of the experimenting done to design these filters and test out CORDIC is available under the `filter/` directory.

All of the math is done in a mixture of 32-bit and 64-bit math, with care to avoid any unnecessary multiplication and to avoid doing any divisions with anything other than a power of 2.
This proved vital in reaching the desired performance of the unit.

### Development notes
All the Python files in `src/` are used to generate constants and headers and stuff.
TODO add these to the Makefile

## How to build

```
cd src/
make
make flash
```

## TODOs
- [ ] Wire up the voltage protection MOSFET correctly
- [ ] Switch out JTAG header with SMD one
- [ ] Add front end filter components
- [ ] Maybe swap to a higher performance MCU
- [ ] Order and test on a longer scale board
- [ ] Test and verify that the board is actually outputting accurate data
