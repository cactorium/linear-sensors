# Linear PCB sensors
This will eventually contain the sensing mechanisms for several different types of digital calipers.
Luckily the patents on all of them have run out, so I can copy a lot of the exact details used in existing calipers, which should mean there's a lot of a better chance of getting good results out of this.
The designs will be made in KiCAD, and will be under a sufficiently liberal license for you guys to use for whatever.
Hopefully these will be cheap and easy enough to use for a lot of interesting applications, like close looping the axes on 3D printers for a lot cheaper than the $1k+ optical scales that's used on higher end models right now.

## Capacitance-based sensor v1
~The capactive sensor appears to be working right now, with a sample rate of 96 samples/sec and a precision of about ~ +-0.06 mm (~ +-0.002in), limited by noise.
The accuracy appears to stay within +- 0.01mm for a lot of the range, but the inaccuracy increases at various points (and also if you're touching the scale) along its range.
It's currently affected moderately strongly by mains noise, the next revision will add better filtering to the front end to reduce this issue.~
So the signal is actually incredibly accurate, as long as the surfaces are closely mating and the amplifier isn't clipping.
I'm getting about ~0.002 mm precision (still need to check accuracy across the full range) after carefully adjusting gain to remove clipping.
The signal doesn't appear anything near a sine wave at the output, it mainly consists of a lot of sharp spikes that I guess the FIRs turn into something closer to a sine wave.
It's currently probably limited by the numerical accuracy of the arctangent operation in the processing, but I need to do more testing to see how accurate it is across its range before tuning its precision any more.

There also appear to be some large inaccuracies across its full range, which also I'm currently working out.

## Capacitance-based sensor v2
I reduced the width of the scale by half to try to improve the form factor and added a second stage of filtering to try to reduce its susceptibility to noise.
I removed the large metallic layer that used to overlap the receiving pad to see if that would reduce the amount of noise.
I'm pretty sure covering it with ground will reduce the output signal by adding a lot of parasitic capacitance, so right now it's bare aside from a trace to get the signal from the receiving pad.
There's now three stages of amplification, the first one, which is adjustable and has a gain from 1x to 10x, and two fixed stages which are 2x and ~10x respectively.
There's several stages of low pass and high pass filtering throughout all this, plus some bypass resistors in case this all turns out wrong so I can revert to the v1 analog circuitry in the worst case.
The edges of the PCB were also rounded just to make it look a little nicer, and the mounting holes are now evenly spaced to make mechanical stuff a lot easier to work out.

The BOM cost is about $16, which is pretty reasonable, but I'll probably try to get it a little lower next revision.

## How they work
Right now I'm looking at two major designs, inductively coupled ones, developed by Mitutoyo, and the T-shaped capacitively coupled ones used in most cheap caliper designs by Mauser-Werke Oberndorf GmbH.
In both cases, the basic gist is that there's a pattern on the stationary bit (called the stator) that affects its coupling with the bit that moves (let's call it the rotor), and in both cases a phase measurement based on measurements as a result of this coupling is used to get a fine measurement, while a counter is used to keep track of how many times the phase has gone about 360 degrees, giving a coarse measurement.
The actual measurement is simply the sum of these two measurements.

In the Mitutoyo design, a pulse is sent into a transmitting coil, which causes it to resonate.
The EM waves produced by this coil are coupled into a pair of receiving coils.
The receiving coils are shaped so that normally the EM waves perfectly cancel out, but the presence and displacement of the disruptors in the stator cause the cancellation to be incomplete.
The receiving coils are shaped so that they form a sine and cosine wave with respect to the displacement relative to the stator.
The receiving coils resonate in series with a capacitor, and a switch is used to stop the resonation near when the voltage across the capacitor is at its peak.
Then the voltage across the capacitors are read using an ADC, and that's used to calculate the displacement within a single stator period.
A counter's used to get the coarser measurement when the stator's moved greater than one period.

In the Mauser-Werke Oberndorf design, there's many transmitting electrodes, each at a different phase.
Each one is shifted by the same amount relative to the one before it.
In the original design, they formed a set of three before it repeated, with relative phases of 0, 120, 240 degrees.
Modern designs tend to use a set of 8, so that's what we'll use here.
These transmitting electrodes couple with the middle of the tee in the stator design, so that the signal read off the T electrode is effectively the capcitively weighted sum of the electrodes that are coupled (physically over) it.
Shifting the rotor causes the ratios to change, allowing an (very good) approximately linear change in phase for a given displacement.
The wider sections of the T are capactively coupled with a receiving electrode on the rotor, and this is filtered and fed into a zero crossing detector to determine the phase different compared with the input signal, giving you a fine measurement of displacement.
The coarse measurement is found by counting, as in the Mitutoyo case.

TODO add patents to repository
