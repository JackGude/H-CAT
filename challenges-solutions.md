---
layout: default
title: Challenges & Solutions - H-CAT
---

# Challenges & Solutions

Developing H-CAT presented several interesting technical and design challenges. Overcoming these hurdles was a key learning experience in this project.

## 1. Powering High-Current LEDs with Arduino Uno

* **Challenge:** The 128 DotStar LEDs, even at moderate brightness, can draw significantly more current (multiple amps) than the Arduino Uno's onboard 5V regulator or USB port can safely supply. Directly powering the LEDs from the Uno's 5V pin would likely damage the board.
* **Solution:** Implemented an external, dedicated **5V 4A DC wall adapter power supply**. This supply connects directly to the LEDs' 5V and GND rails via a panel-mounted DC barrel jack in the enclosure. The Arduino Uno is also powered from this common 5V rail (connected directly to the Uno's 5V pin, bypassing its onboard regulator). A common ground connection between all components ensures proper communication.
* **Learning:** Emphasized the critical importance of proper power budgeting and distribution in embedded systems, especially when dealing with high-power components.

## 2. Achieving a Convincing Holographic Illusion

* **Challenge:** Creating a believable Pepper's Ghost effect requires precise positioning of the light source, the reflector, and careful control of ambient light, all within a compact form factor.
* **Solution:**
    * **Enclosure Design:** Designed a custom enclosure where the DotStar matrices are somewhat hidden, mounted on the top interior, shining downwards into a dark, non-reflective chamber. The acrylic reflector is mounted on the bottom interior, shining upwards towards the viewer.
    * **Reflector Angle Adjustment:** Calculated the optimal acrylic reflector angle, specifically accounting for the viewer's height and distance from the device. The reflector is mounted at ~33 degrees above horizontal (down from 45 degrees), in order to direct the reflected image to a slightly elevated viewer.
* **Learning:** Reinforced principles of optics, 3D design for spatial relationships, and the impact of material properties on visual effects.

## 3. Structural Integrity of Thin-Walled Enclosure

* **Challenge:** Building a sturdy box from 1/8" (3mm) MDF/plywood using only butt joints presented a risk of weak joints prone to splitting or breaking, especially without using screws or nails which are difficult with thin stock.
* **Solution:** Employed **splined butt joints**. After initial butt joints were glued and cured, precise, shallow slots were cut across the joint lines using a Japanese saw. Thin strips of wood (splines) were then glued into these slots, running perpendicular to the joint.
* **Learning:** Gained woodworking experience. I think the splines can be aesthetic as well.

## 4. User Interface Design

* **Challenge:** Designing an intuitive control scheme for multiple modes and custom settings (like color schemes) with a limited number of physical buttons, and ensuring user preferences were saved.
* **Solution:** IN-PROGRESS
* **Learning:** TBD

---