---
permalink: /docs/quick-start/
title: "Quick Start Guide"
layout: single
author_profile: false
sidebar:
  nav: "docs"
---
If you've purchased your very own 8 Bit WiFi Visualizer, here's what happens when you power it up

# Pluggin In

The board accepts micro USB cables and will immediately turn on and begin it's start up functions.

![Power On]({{site.baseurl}}/assets/images/poweron.gif){: .align-center}

It will first scan all the networks that it can see and choose the WiFi channel with the strongest network present. It will then display which network it chose, flashing the leds with the channel number in binary.

# Letting It Run

As the board runs, it will automatically adjust the display scale. If you would like to reset the scale, press the user button once.

# Changing The Channel

![Changing the Channel]({{site.baseurl}}/assets/images/changechannel_small.gif){: .align-center}

If you would like to change the channel that the board is visualizing, press and hold the user button until you see the channel number flashing in binary.

Pressing the user button once will advance to the next channel, cycling through all 11 channels.

Press and hold the button when you have your desired channel number selected to confirm your choice. The board will change channel and begin visualizing the network traffic.


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
