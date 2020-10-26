---
permalink: /docs/
title: "Welcome to the Documentation"
author_profile: false
sidebar:
  nav: "docs"
---

Here you can find more details about how the 8 Bit WiFi Visualizer works, how it was designed, and find instructions to assemble your own!

There is a navigation menu with all the pages within the documentation. If you're still having trouble finding what you're looking for, try the search bar to look through all the pages on this site.

<div class="notice--success"><p style="font-size: medium;"><b>
  Want to ask a question? Suggest a new feature? Report a bug?
  <br><br>
  Add a new Issue on the Github repository with a description of your question or problem and I'll be able to help!</b></p>
</div>

[Create a New Issue!](https://github.com/stasiselectronics/8BitWiFiVisualizer/issues/new){: .btn .btn--success .btn--large}  
*Creating issues requires a Github account*

## Hardware
This is a custom designed Printed Circuit Board, so there are a few parts needed to go from abstract connections to components on copper.



<div style="font-size: 125%;" markdown = "1">
|[Schematics](({{site.baseurl}}/docs/board/schematics/)){: .btn .btn--info .align-center }|The circuit design starts here, take a look to see how all the parts connect together and what their values are.
|[Layout](({{site.baseurl}}/docs/board/layout/)){: .btn .btn--info .align-center }|Here you can find the size and shape of the board, mounting hole locations, and more details about the physical properties of the PCB.
|[Assembly](({{site.baseurl}}/docs/board/assembly/)){: .btn .btn--info .align-center}|Want to build your own? Here you can find the instructions on how to hand solder the surface mount components.
|[Components](({{site.baseurl}}/docs/board/components/)){: .btn .btn--info .align-center }|Here you can find the Bill of Materials, and more information of the specific components that are on the board.

</div>



## Firmware
The ESP82266 WiFi module can be programmed with the Arudiuno language and IDE. This makes getting up and running a snap with plenty of existing libraries for complicated functions.

<div style="font-size: 125%;" markdown = "1">
|[Setting Up]({{site.baseurl}}/docs/firmware/setup/){: .btn .btn--info .align-center }|Learn how to set up the Arduino IDE for developing on this specific board.
|[Blank Sketch]({{site.baseurl}}/docs/firmware/setup/){: .btn .btn--info .align-center }|Want to create your own code? Here's a starting off point with the board specific settings.
|[Packet Visualizer]({{site.baseurl}}/docs/firmware/packet-visualizer/){: .btn .btn--info .align-center}|Learn more about how the Packet Visualizer sketch works.

</div>

