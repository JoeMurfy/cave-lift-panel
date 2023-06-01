## Fiorella's Cave Escape Room Lift Panel

An arduinio script that controls the LED's/switches on a lift control panel. It will take multiple inputs
from 5 different sections.
- Section 1: 7 Switches with integrated LEDs.
- Section 2: 4 Dials.
- Section 3: 8 Rocker Switches with their own LEDs.
- Section 4: 2 Dials.
- Section 5: 4 LEDs indicating which sections (1-4) are completed, 4 Switches with their own LED's.
- LED Level: Rocker switch (single pole double throw) with 4 LED Lights. That will increment/decrement with pushes.

After each section is completed correctly the corresonding LED in section 5 will light. Once all sections are complete and final overide instructions are followed a buzzer will sound to alert games master.

# Requirements
- Arduino Mega (ATMega2560)
- Bounce2 Arduino library
