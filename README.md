# Neopixel protocol decoder for Saleae Logic Analyzer

Decode the 800 kHz protocol used in Neopixel (WS2812) LEDs.

## Installation

1. Install the [Saleae Protocol Analyzer SDK](http://support.saleae.com/hc/en-us/articles/208667926-Protocol-Analyzer-SDK)
2. In the SDK folder, git clone this repo
3. Follow the instructions in the SDK documentation folder to build and
   use the protocol analyzer

## Next steps

1. The signal doesn't properly reset after 50us (the last byte continue
   forever).
2. Provide releases pre-built for the major OSes.

## License

Copyright 2016 Julien Vanier. Released under the MIT license.
