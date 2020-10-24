---
title: "Starting things off"
excerpt_separator: "<!--more-->"
categories:
  - Development Post

---

Welcome to the development blog! Here is where I will be sharing updates to the design, snippets of how to use the board, and anything else that might not fit into the documentation categories.

This blog is starting off at an interesting point: Much of the work for this project has been already completed. I have worked on this design off and on again for the better part of 2 years. Now I am approaching a somewhat "finished" state, so there might not be too many developments to share. However, I still want to have the place to write about what is going on with the design, and to share any nuggets of information that can be illustrated with this design. 

Now, where did things begin?

<h2>A brief history of the design</h2>

This project started off a few years ago when I wanted to learn more about embedded systems and networking. While studying at university, I wanted a project that used the ESP01 modules, those super popular boards that broke out a small handful of GPIO. Because of the limited GPIO, I decided on a minimalist display of only 8 LEDs, being driven by a serial input, parallel output shift register. 

I was inspired by a few projects that used the promiscuous mode of the ESP8266 modules to sniff the packets that were flying through the air. These could display the contents of the packets and try and ascertain any useful information. Now, thanks to SSL certificates and HTTPS, much of any packets you pick up are going to be encrypted (i.e. garbled nonsense). So instead I wanted to use that feature to be able to measure the network activity by counting the number of packets in a given time frame. 

I started off with breadboarding the circuit, taking advantage of the many great tutorials out there on using shift registers to drive LEDs. The next steps after this was to put the components onto a somewhat more permanent solution: prototyping board. These boards have plated holes for through hole components spaced 2.54 mm apart from each other. They accept all the through hole parts, but require jumper wires to be soldered onto the pins to connect everything together. 

After completing this build I left it alone for a bit, letting it be the blinking desk toy that I wanted.

<h3>Then I started learning how to design printed circuit boards</h3>
I certainly learned a lot from my university classes, but there were some gaps in the practical skills of going from theory to application. Most of my PCB design experience came from on the job, working as an Embedded Systems Engineer. So, while working to develop mass produced circuit boards, I wanted to try my hand at updating the little desk toy I had made some time ago.

I first used Altium to capture the schematic and layout the PCB. This was mostly due to the fact that I was using Altium on the job, so it was an easy choice. I then used OSH Park to fabricate a few boards and assembled with the SMD components I had lying around. 

This board worked, but not without a few hiccups. 

After some time, and a move to Europe, I wanted to take a crack at fixing those problems that came with the first PCB design. I also wanted to learn how to use KiCAD, to make sure that I can share the design with others that might not have access Altium.

<h3>Picking up where I left off</h3>
I first submitted the initial commits for this project back in November of 2019. I updated the schematic, rerouted the board, and made the shift to the ESP Wroom 02 module. This was a big change from the ESP01 modules that I was using before. I wanted the design to be a more polished assembly.

I sent the gerber files off to JLCPCB for fabrication, and purchased for more SMD parts. After the long wait for shipping (save money, or time? hard to do both), I threw together one assembly.

Much to my dismay, there were still problems. So I left it again, to sit in a project box collecting dust.

<h3>Pushing through failure</h3>

Late in the summer of this year, I decided to try again with the design. I wanted take up the challenge of getting the design working, and share it with the open source community. I also wanted to challenge myself with design for manufacturing. It is one thing to build one of something, but it is another challenge to make a larger quantity.

So now, with over 100 commits to the repository, the design is on its way to a finished state ready for others to replicate or purchase the small run of assembled boards or kits. 

<h3>What's next?</h3>

Now that the board is in a final state, parts have been ordered and bare PCBs are on the way. I need to finish up the documentation here on this site, as well as start offering kits and assemblies for sale.



