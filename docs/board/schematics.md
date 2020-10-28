---
layout: single
permalink: /docs/board/schematics/
title: "Schematics"
author_profile: false
sidebar:
  nav: "docs"
---
Here you can find more information about the different components that are included on the schematic. These are symbols that represent the inputs and outputs of the electrical components that make the board work.

[Download a PDF of the Schematics](https://github.com/stasiselectronics/8BitWiFiVisualizer/raw/master/Hardware%20Files/PDFs/8Bit_WiFi_Visualizer_Schematic.pdf)

The schematics are broken down into the following parts:
-   WiFi Module
-   Power Supply
-   Display
-   User Input
-   Programming

## WiFi Module
![ESP8266]({{site.baseurl}}/assets/images/schematic_wifi_module.png){: .align-center}
The ESP WROOM 02 acts as the microcontroller for this design. It is a module that includes both the ESP8266 and a WiFi antenna that is made using a trace on the module's circuit board. This means that we get all the parts needed to make the microcontroller and WiFi work on one simple module. We only have to worry about a few power filtering capacitors and a pull down resistor on pin 6, GPIO 15. This pull down resistor is used for making sure the WiFi module doesn't try and boot from an SD card on startup. 

Want a deep dive into how this module works and what's needed to add one to your design?  
[Check out the datasheet from Espressif](https://www.espressif.com/sites/default/files/documentation/0c-esp-wroom-02_datasheet_en.pdf)

### Inputs and Outputs
There are a few inputs and outputs that we need to worry about to get all the lights blinking in just the right way.

#### UART
This is the communication protocol used to program the module and read any debug information as it is running.

|---
| Name | Direction | Description
|:-|:-:|:-
| ESP_RX | **input**  | Serial Communication going to the WiFi module
| ESP_TX | **output** | Serial Communication coming from the WiFi module

These signals will be routed to the programming header `J2`.

#### Shift Register

In order to put data from the WiFi module (a packet of 8 bits, corresponding to which LED to turn on) we need to attach some GPIO signals between the WiFi module and the shift register `U2`.

|---
| Name | Direction | Description
|:-|:-:|:-
| CLOCK | **output** | clock input for all d flip-flops
| LATCH | **output** | causes whatever data is in the shift register to appear on the output
| CLEAR | **output** | clears whatever data is in the shift register (sets to 0), active low
| OUTPUT_ENABLE | **output** | allows output to be either 1 or 0, if disabled they will become high impedance, active low
| DATA | **output** | serial data input stream, this is what gets 'clocked' in

<h4>Active Low or Active High?</h4>

Most digital signals are "Active High", the circuit sees a digital 1 when the voltage is at or near the supply voltage (here it's 3.3 V).

"Active Low" signals are the opposite, and require a low voltage (at or near 0 V) to indicate a logical 1 or to do something. For us, the `CLEAR` and `OUTPUT_ENABLE` signals are **Active Low**. Therefore we will set them to 0 V when we want them to do the thing their name implies.

Chips will use Active Low signals to help reduce the chance of errors resulting from electrical noise. When we are applying a voltage above ground, noise from all sorts of sources can cause that voltage to swing, possibly below the threshold for what the IC sees as "high". 

When signals have a clear path to ground (or are directly connected to ground), it is a lot harder for noise to appear, since any voltage will quickly dissipate.

[learn more about how logic levels work](https://wikipedia.org/wiki/Logic_level)

## Power Supply
![Power Supply]({{site.baseurl}}/assets/images/schematic_powersupply.png){: .align-center}

This part of the circuit is what takes the input voltage from the USB connector (or the programming header) and regulating the voltage down to 3.3 Volts for the rest of the components. It is a smiple Low Dropout Linear Regulator (LDO). This means that it will "burn off" extra voltage on the input and create the voltage we want on the output. One downside to these types of regulators is that they can waste some energy, which turns to heat coming out of the part. 

We can assume the USB port has a voltage of around 5 V, but what if someone gives the board another voltage?

The voltage regulator (Diodes Incorporated `AZ1117CH-3.3TRG1`) has a rated max input voltage of 15 Volts, and voltage dropout of 1.3 Volts at 800 mA. This means the board can safely accept a voltage of between 4.6 and 15 Volts. If the input voltage starts dropping below 4.6 V, then the output voltage will also start to drop, which can affect the performance of the rest of the circuit.

[Learn more about LDO regulators specifications](https://www.ti.com/lit/an/slva079/slva079.pdf)

## Display
Here is the circuit that takes the data coming from the microcontroller and outputs that data on the 8 LEDs.  
### Shift Register
![Display]({{site.baseurl}}/assets/images/schematic_led_driver.png){: .align-center}
<h4>Why do we even need this?</h4>
Good question! Often times we need to ask ourselves this, to be able to justify our design decisions so that we don't assume we're making the right decision and so we know we are making the right one.

An alternative to using this extra IC is to just simply hook up the 8 LEDs directly to GPIO on the WiFi module. In order to do this however, we would take up a lot of ports and have to use some that are needed for programming. 

Using a shift register allows us to use less GPIO ports, and even allows the design to expand past 8 LEDs without needing extra signals coming from the WiFi Module. At the cost of extra parts, we gain simplicity and a chance to learn about how to use a nifty part!

<div class="notice--info">
  <h4>Maybe you could make do without it?</h4>
  <p>Want a chance to reduce how many parts are in the circuit (and therefore cost)? See if you can redesign the circuit to do away with the shift register!</p>
</div>


### LEDs
![Display]({{site.baseurl}}/assets/images/schematic_led_array.png){: .align-center}


## User Input
![User Input]({{site.baseurl}}/assets/images/schematic_user_switch.png){: .align-center}
## Programming
![Programming]({{site.baseurl}}/assets/images/schematic_programming.png){: .align-center}