---
permalink: /docs/firmware/setup/
title: "Setting Up Arduino"
layout: single
author_profile: false
sidebar:
  nav: "docs"
---
Want to start writing your own Arduino sketches and upload them to the board?

Just in case you haven't already, here's the link to [download Arduino](https://www.arduino.cc/en/software).

If you want to use the Arduino IDE to write and upload new firmware to the ESP8266 module, you'll need to do some setup before Arduino can compile and flash your sketch.

# Adding ESP8266 to the Arduino IDE

First up is the ESP8266 Arduino Core. From their github page:

>This project brings support for the ESP8266 chip to the Arduino environment. It lets you write sketches, using familiar Arduino functions and libraries, and run them directly on ESP8266, with no external microcontroller required.

You can view the source for this project [here](https://github.com/esp8266/Arduino).

## Adding new Board Manager URL



Arduino allows you to add more sources for the board manager to look for extra boards to add. This allows you choose the ESP8266 from the `Tools -> Board` list. Copy the following URL to your clipboard.

<kbd id="BoardURL" style="overflow-wrap: break-word;"> https://arduino.esp8266.com/stable/package_esp8266com_index.json </kbd>

### Open Preferences
Start the Arduino IDE and select `File -> Preferences`. This will open up the following window:

![Arduino Preferences]({{site.baseurl}}/assets/images/arduinopreferences.png){: .align-center}

In the text field `Additional Board Manager URLs`, paste the URL for the ESP8266 package and click `OK` to confirm the changes.

![Arduino Preferences]({{site.baseurl}}/assets/images/arduinoboardurl.png){: .align-center}

<div class="notice--info">
If you have more than one URL to add, you can press the button next to the text field to open another dialog box. Here you can add each URL on a new line. Below, you can see how to have both the ESP8266 and the ESP32 added to the board manager.
</div>

![Arduino Preferences]({{site.baseurl}}/assets/images/arduinoextraboards.png){: .align-center}

### Install the new board
Now that Arduino can find the ESP8266 boards, we need to use the board manager to install the latest version.

Select `Tools -> Boards -> Board Manager` to display the board manager window.

![Arduino Board Manager]({{site.baseurl}}/assets/images/arduinoboardmanager.png){: .align-center}

Use the text field to search for `ESP8266`, or if you're feeling freaky, scroll down until you find the board. Click `Install` to grab the latest version of the ESP8266 Arduino Core. This will make it possible to select the ESP8266 module as a board to upload to.

![Arduino Board Manager with ESP8266]({{site.baseurl}}/assets/images/arduinoboardsmanageresp8266.png){: .align-center}

<div class="notice--info">
If you can't find the board listed, make sure the URL was entered correctly in the preferences window.
</div>
