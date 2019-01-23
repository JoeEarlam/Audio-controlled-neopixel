# Audio-controlled-neopixel

Filters an incoming line level audio signal into three bandpassed frequency "bins", which output to a peak detect sample and hold circuit. These sample and holds are sampled by the Arduino ADC, and the three frequencies (bass, mid, treble) become RGB on a Neopixel compatible LED strip.

There are a few different patterns currently written - a mixture of sound activated, random, block updated and "chasing lights" patterns.

# Hardware Notes, in no particular order.

There are two options for power. +5V only using a Tracopower TMA0512D to generate the +/-12V voltages required for the analogue components, or external +/-12V and 5V. 5V only is preferred for simplicity, but the TMA0512D isn't a typical parts bin find (and is the single most expensive component on the board), so an external power header has been added for operation without.

The level potentiometer allows a wide range of signals to be used. Turn it up until the peak light begins to flash, then down a little. This gives you maximum brightness from the Neopixel strip without clipping.

Follow Adafruit's guidance on Neopixel power supplies - the 5V rail will need to be beefy. The PCB can handle up to around 5A - ensure the fitted fuse is suitable.
