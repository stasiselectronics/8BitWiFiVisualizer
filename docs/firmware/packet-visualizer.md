---
permalink: /docs/firmware/packet-visualizer/
title: "Packet Visualizer Sketch"
layout: single
author_profile: false
sidebar:
  nav: "docs"
---
<!-- Mathjax Support -->
<script type="text/javascript" async
  src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-MML-AM_CHTML">
</script>

<div class="notice--warning">
  <h4>This page is a work in progress</h4>
  <p>I'm currently working on adding content to this page, make sure to check back later!</p>
</div>

This is the firmware that turns the 8 Bit WiFi Visualizer board into a Network Visualizer by counting how quickly packets are being sent on the WiFi channel.

Want to skip to the automatic firmware version?

[Skip Ahead]({{site.baseurl}}/docs/firmware/packet-visualizer/#automatic-firmware){: .btn .btn--success}

Be sure to check the source for the latest firmware. I will try and update this documentation if there are major updates, but for minor tweaks and formatting fixes be sure to view the latest.

[View Source](https://github.com/stasiselectronics/8BitWiFiVisualizer/tree/master/Firmware%20Files){: .btn .btn--success}

# Basic Firmware

This version of the firmware provides the bare minimum to get the network visualizer working. It requires you to setup a few global variables that affect the functionality:

## Global Variables

These are variables that are configurable, and used throughout the sketch. Feel free to adjust these to your network conditions.

| Name | Description |
|---|
| ap_channel | This is the network channel that the board will count packets on. It can only be on one channel at a time. Most users will set this to their own network's channel (1 through 11)  |
| max_rate | This is the maximum rate of packets per second that will be displayed. It will be divided by eight for the 8 LEDs.  |
| refresh_rate | This is how often the display is updated, and is used in calculating the packets per second. |
| led_brightness | This will used in Pulse Width Modulation for the output enable pin of the shift register. Use a value between 0 and 1023, where 1023 is "off", and 950 is "dim" |



```c++
int ap_channel = 1;
double max_rate = 1000;
int refresh_rate = 100;
int led_brightness = 950;
```

## Header Files

```c++
#include <ESP8266WiFi.h>
```
## GPIO Definitions

```c++
#define LATCH 5
#define CLOCK 4
#define DATA 16
#define SWITCH 14
#define CLEAR 12
#define OUTPUTENABLE 13
```

## Packet Counting

```c++
unsigned volatile long pkts = 0;

void counter() {
  pkts++;
}
```

## Setup

### Serial Communication

```c++
Serial.begin(115200);
Serial.print("\n\n\n");
```

### Network Configuration

```c++
if(ap_channel<1||ap_channel>14){
  ap_channel=1;
  Serial.println("AP Channel out of bounds, set ap_channel to something between 1 and 14");
}
wifi_set_opmode(STATION_MODE);
wifi_set_channel(ap_channel);
```

### Setting up Callback Function

```c++
wifi_promiscuous_enable(0);
wifi_set_promiscuous_rx_cb((wifi_promiscuous_cb_t)counter);
wifi_promiscuous_enable(1);
```

### GPIO Port Configuration

```c++
pinMode(LATCH, OUTPUT);
pinMode(CLOCK, OUTPUT);
pinMode(DATA, OUTPUT);
pinMode(CLEAR, OUTPUT);
pinMode(OUTPUTENABLE, OUTPUT);
```

### Initial Pin Conditions

```c++
digitalWrite(CLEAR, HIGH);
analogWrite(OUTPUTENABLE, led_brightness);
```

## Loop

### Timing

```c++
static unsigned long prevTime = 0;
static byte previous_value = 0;
ESP.wdtFeed();
if(millis() - prevTime >= refresh_rate){
  prevTime = millis();
  // ...
  // ...
  // ...
}
```

### Calculating Packets Per Second

```c++
double packets_per_second = (pkts*(1000/refresh_rate));
pkts = 0;
```

### Converting Packets Per Second to LEDs

```c++
byte led_value = pow(2,ceil((packets_per_second/max_rate)*8.0)) - 1;
```

\\[ a^2 = b^2 + c^2 \\]

### Driving the LEDs

```c++

```

###



# Automatic Firmware
