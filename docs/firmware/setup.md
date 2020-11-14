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



Arduino allows you to add more sources for the board manager to look for extra boards to add. This allows you choose the ESP8266 from the `Tools->Board` list. Copy the followi

<kbd id="BoardURL" style="overflow-wrap: break-word;"> https://arduino.esp8266.com/stable/package_esp8266com_index.json </kbd>


<button onclick="boardurlcopy()" class="btn--info">Copy Board URL</button>


<script>
function boardurlcopy() {
  var copyText = document.getElementById("BoardURL");
  copyText.select();
  copyText.setSelectionRange(0, 99999)
  document.execCommand("copy");
  alert("Copied Board URL");
}
</script>
