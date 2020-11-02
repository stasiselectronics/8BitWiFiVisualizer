---
permalink: /docs/firmware/packet-visualizer/
title: "Packet Visualizer Sketch"
layout: single
author_profile: false
sidebar:
  nav: "docs"
---
This is the firmware that turns the 8 Bit WiFi Visualizer board into a Network Visualizer by counting how quickly packets are being sent on the WiFi channel.

Want to skip to the automatic firmware version?

[Skip Ahead]({{site.baseurl}}/docs/firmware/packet-visualizer/#automatic-firmware){: .btn .btn--success}

Be sure to check the source for the latest firmware. I will try and update this documentation if there are major updates, but for minor tweaks and formatting fixes be sure to view the latest.

[View Source](https://github.com/stasiselectronics/8BitWiFiVisualizer/tree/master/Firmware%20Files){: .btn .btn--success}

# Basic Firmware

This version of the firmware provides the bare minimum to get the network visualizer working. It requires you to setup a few global variables that affect the functionality:

## Global Variables

| Name | Description |
|---|
| ap_channel | This is the network channel that the |
| max_rate | cell |
| refresh_rate | cell |
| led_brightness | cell |


```c++
int ap_channel = 1;
double max_rate = 1000;
int refresh_rate = 100;
int led_brightness = 950;
```


# Automatic Firmware
