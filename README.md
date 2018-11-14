# Audio-controlled-neopixel

Filters an incoming line level audio signal into three bandpassed frequency "bins", which output to a peak detect sample and hold circuit. These sample and holds are sampled by the Arduino ADC, and the three frequencies (bass, mid, treble) become RGB on a Neopixel compatible LED strip.

Currently only one pattern is implemented on the strip, a "chasing lights" pattern where the most recent sample is set at pixel 0, and then shifted along the strip one position so that the new sample can be set at pixel 0 again.