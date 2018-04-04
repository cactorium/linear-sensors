# Linear PCB sensors (WIP!)
This will eventually contain the sensing mechanisms for several different types of digital calipers.
Luckily the patents on all of them have run out, so I can copy a lot of the exact details used in existing calipers, which should mean there's a lot of a better chance of getting good results out of this.
The designs will be made in KiCAD, and will be under a sufficiently liberal license for you guys to use for whatever.
Hopefully these will be cheap and easy enough to use for a lot of interesting applications, like close looping the axes on 3D printers for a lot cheaper than the $1k+ optical scales that's used on higher end models right now.

## How they'll work
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
