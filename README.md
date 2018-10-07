# Neopixel protocol decoder for Saleae Logic Analyzer

Decode the 800 kHz protocol used in Neopixel (WS2812) LEDs with a Saleae-brand logic analyzer.

Provides bytes above the bit data stream.

## Installation

1. Install the [Saleae Protocol Analyzer SDK](http://support.saleae.com/hc/en-us/articles/208667926-Protocol-Analyzer-SDK)
2. In the SDK folder, git clone this repo
3. Follow the instructions in the SDK documentation folder to build and
   use the protocol analyzer

## Next steps

1. Provide test data for use in developing the protocol decoder as recommended in the Saleae documentation.
2. Group the bytes into 24-bit groups and show the actual LED color!
3. Provide releases pre-built for the major OSes.

## License

Copyright 2016 Julien Vanier. Released under the MIT license.
