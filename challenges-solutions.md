---
layout: default
title: Challenges & Solutions - H-CAT
---

Developing H-CAT presented several interesting technical and design challenges. Overcoming these hurdles was a key learning experience in this project.

## 1. Powering High-Current LEDs with Arduino Uno

* **Challenge:** The 128 LEDs, even at moderate brightness, can draw significantly more current than the Arduino Uno's onboard 5V regulator or USB port can safely supply. Directly powering the LEDs from the Uno's 5V pin would likely damage the board.
* **Solution:** This problem actually led to an improvement in the project overall, the embedded USB-C port (instead of a dedicated power cable running from the box). I needed an external, dedicated 5V 4A DC wall adapter power supply to power both the lights and the arduino. This power supply connects to a port in the side of the device, which then splits the power to 5V and GND busses inside the unit, via a barrel jack adapter inside the box. **The Arduino Uno is also powered from these common rails.** A common ground between all components ensures proper communication.
* **Learning:** Emphasized the critical importance of proper power budgeting and distribution in embedded systems, especially when dealing with high-power components.

## 2. User Interface Design

* **Challenge:** Designing an intuitive control scheme for multiple modes and custom settings with a limited number of physical buttons, and ensuring user preferences were saved.
* **Solution:** Set up a finite state machine to handle the different modes and submodes. The mode button cycles through the different modes, and the submode button cycles through the different submodes for the current mode. The switched potetionmeter controls both the brightness of the LEDs and the on/off functionality. The brightness, mode, and color settings are saved to EEPROM so that it persists between power cycles.
* **Learning:** Gained more experience with embedded systems and the use of finite state machines, as well as the use of EEPROM to store user preferences.


## 3. Enclosure Design

* **Challenge:**
  * ~~Building a sturdy box from thin MDF/plywood using only butt joints presented a risk of weak joints prone to splitting or breaking. However the material is too thin to use screws or nails.~~
  * The enclosure needed to organize all of the electronic components in a very specific configuration to achieve the intended effect.
  * The enclosure needed to be as compact as possible, while still allowing for easy access to the components.
* **Solutions:**
  * My initial solution was a fairly compilcated but (I would argue) elegant hand-carved wooden puzzle box. I realized I have access to a 3D printer through school, so I was able to practice my CAD skills and just print a case. This is much easier, cheaper, and more reporoducable than the previous method. It's an improvement in every way.
  * ~~Employed **splined butt joints**. After initial butt joints were glued and cured, precise, shallow slots were cut across the joint lines using a hand saw. Thin strips of wood (splines) were then glued into these slots, running perpendicular to the joint.~~
  * ~~Again, **the problem leads to the solution.** These splines provide an excellent basis to split the enclosure into two main chambers. One for the electronics, and one for the display. The front half of the box contains the display LED and the projector. The back half contains the Arduino, RTC, and power distribution setup. More splines in the top-front of the box provide the mounting points for the LED matrixes. The base underneath the acrylic reflector is also splined into the box. This spline will hide the weights in the bottom of the box.~~
  * The planned dimensions of the final product are **2.25" x 2.25" x ~3.7"**. The width is determined by the width of the arduino. The depth is set to the width to make the base square. (Technically we could probably get away with ~1.8" for depth, but there's no need.) The height is set by the longest dimension of the Arduino. The Uno is mounted to the chamber dividing wall with velcro, so that it can be removed for programming. The power distribution board is mounted to the arduino (with spacers for airflow) with double-sided tape. The back panel is removable and attached with magnets. The magnets for the back panel are also mounted on splines in the back of the box. Several cuts are made towards the back of the box and are not splined in order to allow for airflow.
* **Learning:** Gained practical experience in project planning and design, working within tight constraints to integrate all project components neatly into a single sturdy, aesthetically pleasing enclosure, and do it cheaply. Designed and planned the entire project start to finish before ordering any components. Got some experience with 3D printing and CAD.

## 4. Achieving a Convincing Holographic Illusion

* **Challenge:** Creating a believable Pepper's Ghost effect requires precise positioning of the light source, the reflector, and careful control of ambient light, all within a compact form factor.
* **Solution:**
  * **Enclosure Design:** Designed a custom enclosure where the DotStar matrices are somewhat hidden, mounted on the top interior, shining downwards into a dark, non-reflective chamber. The acrylic reflector is mounted on the bottom interior, shining upwards towards the viewer.
  * **Reflector Angle Adjustment:** Calculated the optimal acrylic reflector angle, specifically accounting for the viewer's height and distance from the device. The reflector is mounted at ~33 degrees above horizontal (down from 45 degrees), in order to direct the reflected image to a slightly elevated viewer (optimized for sitting at a desk, roughly arms length and 1.3 feet above horizontal).
* **Learning:** Reinforced principles of optics, 3D design for spatial relationships, and the impact of material properties on visual effects.

## In-Progress Challenges

* **Challenge:** Filled up both RAM and Flash memory in the arduino. I was able to get all three modes running minimally on one screen with the R3 Uno, but as soon as I added the second screen, I began to have memory problems.
* **Solution:**
  * Long-term: Upgrade from an R3 to an R4 Minima. It's cheap and solves the memory problem forever. Also requires almost no changes to the existing project design.
  * Short-term: I was able to disable the extra modes and continue development on one mode at a time while waiting for the replacement board. I was able to upload my custom font for the clock mode to the flash memory of the arduino as well in order to free up a little more RAM.
* **Learning:** Gained extremely useful hands-on experience working at the edge of memory limits with embedded devices.

---

* **Challenge:** Ran into a bug with the R4 Minima that caused massive slowdowns when using the arduino random library.
* **Solution:** After some research online I was able to confirm that this is a known issue after reports from other users. To solve the problem I implemented my own random library using the signal from an empty analog pin to generate a random number.
* **Learning:** Gained experience troubleshooting code problems caused by a hardware revision.

---
