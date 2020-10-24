# 8 Bit WiFi Visualizer
Open Source Hardware project for a minimalist WiFi enabled 8 Bit visualizer. This design uses the popular ESP8266 wifi module to drive 8 LEDs with a shift register.

## Network Traffic Visualizer
Want to visualize how busy your WiFi channel is? The included Arduino sketch measures how many packets are flying around on the selected channel and displays the intensity on the LEDs.

With the help of some automated functions, the board selects the WiFi channel with the strongest network present at startup. It then automatically adjusts the display range to keep up changing network conditions.

[Learn more about how this firmware works!](https://stasiselectronics.github.io/8BitWiFiVisualizer/docs/enclosure/automatic-firmware/)

<p align="center">
  <img src="https://raw.githubusercontent.com/ChandlerMcCowan/8BitWiFiVisualizer/master/Hardware%20Files/3D%20Model/8Bit_WiFi_Visualizer_PCBA.png" alt="Render" width="600"/>
</p>

This repository contains all the source files needed to reproduce this project. The PCB is designed with KiCAD and the firmware uses Arduino for the ESP8266.

This is still a work in progress, so be sure to check back for future updates!

## Companion Site

[Check out the companion site for more documentation!](https://stasiselectronics.github.io/8BitWiFiVisualizer/)


## Quick Links
- [Board Schematics](https://github.com/stasiselectronics/8BitWiFiVisualizer/blob/master/Hardware%20Files/PDFs/8Bit_WiFi_Visualizer_Schematic.pdf)


## Current Status

This project is nearing completion, here are some of the latest updates
- Redesigned PCB for larger components to make hand soldering easier
- Recovered old firmware and tested on prototype board
- Assembled and tested latest PCB design
- Major firmware updates
    - Auto selecting AP channel on startup
    - Auto ranging intensity scale with linear decay
    - Change AP channel with user button

## Future Goals

Here's what needs to get done for this project:
- Complete Documentation

Most of the project is now complete, so now all that is left is to finish up the documentation

