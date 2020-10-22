---
permalink: /docs/quick-start/
title: "Quick Start Guide"
layout: single
author_profile: false
sidebar:
  nav: "docs"
---
# Automatic Firmware

The firmware that ships with the board automatically sets up the network settings and display settings to visualize the network traffic.

All you need to do is plug a micro USB cable in and let the board do the rest. 

If you want to reset the automatic display range, simply press the button and the board will reset the number of packets per second that registers 8 LEDs on. As the board runs, it looks for any packets per second rates that is larger than its current maximum, and updates the maximum to that. This means the board should automatically adjust the display range.

If you want, you can change the AP Channel that the ESP8266 is currently looking at. Simply hold down the user button (lower right) until the LEDs flash, showing the currently selected channel. Press the button again, to advance to the next channel. The channel number will be displayed in binary, and will cycle the channels between 1 and 11. 

When you have the channel you want, hold the button down again to confirm the selection. The board will change to that channel.

Want to learn more about how this firmware works?  
[Check out the source](https://github.com/stasiselectronics/8BitWiFiVisualizer/blob/master/Firmware%20Files/PacketVisualizer_auto/PacketVisualizer_auto.ino)


# Basic Firmware

If you know what AP channel you want to look at and what your maximum rate should be, you can use the basic firmware version and flash the board with an external USB to UART board or cable. 

Want to see what a very basic version of the Packet Visualizer looks like?  
[Check out the source](https://github.com/stasiselectronics/8BitWiFiVisualizer/blob/master/Firmware%20Files/PacketVisualizer_auto/PacketVisualizer_auto.ino)

# Reprogramming

Want to reprogram the board with some custom firmware? Here's how.

## Adding ESP8266 to the Arduino IDE

If you want to use the Arduino IDE to write and upload new firmware to the ESP8266 module, you'll need to do some setup before Arduino can compile and flash your sketch.

The ESP8266 Arduino Core is an open source project

Add this to the Arduino IDE under the Additional Board Manager URLs


