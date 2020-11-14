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



Arduino allows you to add more sources for the board manager to look for extra boards to add. This allows you choose the ESP8266 from the `Tools->Board` list. Copy the following URL to your clipboard.

<kbd id="BoardURL" style="overflow-wrap: break-word;"> https://arduino.esp8266.com/stable/package_esp8266com_index.json </kbd>

### Open Preferences
Start the Arduino IDE and select `File->Preferences`. This will open up the following window:

![Arduino Preferences]({{site.baseurl}}/assets/images/arduinopreferences.png){: .align-center}

In the text field `Additional Board Manager URLs`, paste the URL for the ESP8266 package.

![Arduino Preferences]({{site.baseurl}}/assets/images/arduinoboardurl.png){: .align-center}

<div class="notice--info">
If you have more than one URL to add, you can press the button next to the text field to open another dialog box. Here you can add each URL on a new line.
</div>
