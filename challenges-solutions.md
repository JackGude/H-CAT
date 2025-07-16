---
layout: default
title: Challenges & Solutions - H-CAT
---

# Challenges & Solutions

Developing H-CAT presented several interesting technical and design challenges. Overcoming these hurdles was a key learning experience in this project.

## 1. Powering High-Current LEDs with Arduino Uno

* **Challenge:** The 128 DotStar LEDs, even at moderate brightness, can draw significantly more current (multiple amps) than the Arduino Uno's onboard 5V regulator or USB port can safely supply. Directly powering the LEDs from the Uno's 5V pin would likely damage the board.
* **Solution:** This problem actually led to an improvement in the project overall, the embedded USB-C port (instead of a dedicated power cable running from the box). I needed an external, dedicated 5V 4A DC wall adapter power supply to power both the lights and the arduino. This power supply connects to a port in the side of the H-CAT, which then splits the power to 5V and GND rails on a small breadboard inside the unit, via a barrel jack adapter inside the box. **The Arduino Uno is also powered from this common 5V rail.** The Uno is connected directly to the 5V rail, bypassing its onboard regulator. A common ground connection between all components ensures proper communication.
* **Learning:** Emphasized the critical importance of proper power budgeting and distribution in embedded systems, especially when dealing with high-power components.

## 2. Achieving a Convincing Holographic Illusion

* **Challenge:** Creating a believable Pepper's Ghost effect requires precise positioning of the light source, the reflector, and careful control of ambient light, all within a compact form factor.
* **Solution:**
    * **Enclosure Design:** Designed a custom enclosure where the DotStar matrices are somewhat hidden, mounted on the top interior, shining downwards into a dark, non-reflective chamber. The acrylic reflector is mounted on the bottom interior, shining upwards towards the viewer.
    * **Reflector Angle Adjustment:** Calculated the optimal acrylic reflector angle, specifically accounting for the viewer's height and distance from the device. The reflector is mounted at ~33 degrees above horizontal (down from 45 degrees), in order to direct the reflected image to a slightly elevated viewer (optimized for sitting at a desk, roughly arms length and 1.3 feet above horizontal).
* **Learning:** Reinforced principles of optics, 3D design for spatial relationships, and the impact of material properties on visual effects.

## 3. Enclosure Design

* **Challenge:** 
    * Building a sturdy box from thin MDF/plywood using only butt joints presented a risk of weak joints prone to splitting or breaking. However the material is too thin to use screws or nails.
    * The enclosure needed to organize all of the electronic components in a very specific configuration to achieve the intended effect.
    * The enclosure needed to be as compact as possible, while still allowing for easy access to the components. 
* **Solutions:** 
    * Employed **splined butt joints**. After initial butt joints were glued and cured, precise, shallow slots were cut across the joint lines using a hand saw. Thin strips of wood (splines) were then glued into these slots, running perpendicular to the joint.
    * Again, the problem leads to the solution. These splines provide an excellent basis to split the enclosure into two main chambers. One for the electronics, and one for the display. The front half of the box contains the display LED and the projector. The back half contains the Arduino, RTC, and power distribution setup. More splines in the top-front of the box provide the mounting points for the LED matrixes. The base underneath the acrylic reflector is also splined into the box. This spline will hide the weights in the bottom of the box.
    * The planned dimensions of the final product are **2.25" x 2.25" x ~3.7"**. The width is determined by the width of the arduino. The depth is set to the width to make the base square. (Technically we could probably get away with ~1.8" for depth, but there's no need.) The height is set by the longest dimension of the Arduino. The Uno is mounted to the chamber dividing wall with velcro, so that it can be removed for programming. The power distribution board is mounted to the arduino (with spacers for airflow) with double-sided tape. The back panel is removable and attached with magnets. The magnets for the back panel are also mounted on splines in the back of the box. Several cuts are made towards the back of the box and are not splined in order to allow for airflow.
* **Learning:** Gained practical experience in project planning and design, working within tight constraints to integrate all project components neatly into a single sturdy, aesthetically pleasing enclosure, and do it cheaply. Designed and planned the entire project start to finish before ordering any components.

## 4. User Interface Design

* **Challenge:** Designing an intuitive control scheme for multiple modes and custom settings (like color themes) with a limited number of physical buttons, and ensuring user preferences were saved.
* **Solution:** IN-PROGRESS
* **Learning:** TBD

---