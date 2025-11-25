![Cover](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/Cover_1.jpg)

# DIY Geiger Counter
This project is a fully functional DIY Geiger counter built around an M4011 Geiger–Müller tube, a custom two-board PCB design, and a retro-style five-digit seven-segment display. It’s portable, battery-powered and easy to build yourself.
The device measures radiation in µS/h, cpm, and raw counts, with settings stored in EEPROM. Navigation is handled by two buttons, and the counter provides both visual and audible feedback for detected radiation pulses. The project includes a 3D-printed housing with optional decorative elements.  
All PCBs and the stencil for this project were fabricated by [PCBWay](https://www.pcbway.com/), whose quality and service helped make the build smooth and enjoyable.  
This repository includes schematics, PCB files, firmware, STL files, and documentation so you can build your own portable Geiger Counter from scratch. You can find the full blog on Instructables: [DIY Geiger Counter](https://www.instructables.com/DIY-Geiger-Counter/)


**NOTE:**  
Version 3 of the main PCB is planned to address low-voltage limitations of the MT3608 boost converter. Version 2 users are encouraged to add a 100 µF capacitor across 5V and GND for improved stability.


***
# FEATURES
- Detects radiation using an M4011 Geiger-Müller tube
- Displays measurements in µS/h, cpm, or counts
- Simple navigation using two buttons: switch modes, reset counts, and access settings
- Configurable options saved in EEPROM: battery type, sound, and LED indicators
- Retro-inspired five-digit seven-segment display powered by two AA batteries


***
# PROGRAMMING
Programmed with the Arduino IDE and [MiniCore board manager](https://mcudude.github.io/MiniCore/package_MCUdude_MiniCore_index.json). No external library is required, everything is included in the sketch!


***
# ELECTRIC COMPONENTS - HIGH VOLTAGE CIRCUIT:
| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| 1nF | 1 | C1 |
| 10nF | 2 | C2,C3 |
| 220pF | 2 | C4,C5 |
| 1N914 | 1 | D1 |
| 1N4937 | 1 | D2 |
| 5x20 Fuse Clip | 2 | J1-J4 |
| 5P-2.54 Header | 2 | J5,J6 |
| 10mH Inductor | 1 | L1 |
| 2N3904 | 2 | Q1,Q3 |
| FJN3303 | 1 | Q2 |
| 220k | 1 | R1 |
| 1k | 1 | R2 |
| 330r | 1 | R3 |
| 100k | 2 | R4,R9 |
| 8.2r | 1 | R5 |
| 10r potentiometer | 1 | R6 |
| 4.7M | 1 | R7 |
| 22k | 1 | R8 |
| 10k | 1 | R10 |
| TLC555 | 1 | U1 |
| M4011/J302/SI-3BG | 1 | - |


***
# ELECTRIC COMPONENTS - MAIN BOARD V3 CIRCUIT:
| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| BH-AA-A5BJ012 | 1 | B1,B2 |
| Passive Buzzer 12x9.5 | 1 | BUZ1 |
| 22uF 0805 | 2 | C1,C2 |
| 100nF 0805 | 8 | C3-C6,C11-C13,C18 |
| 22pF 0805 | 2 | C7,C8 |
| 10uF 0805 | 1 | C9 |
| 1uF 0805 | 2 | C10,C17 |
| 100pF 0805 | 2 | C14,C15 |
| 100uF 1206 | 2 | C14,C15 |
| 6P (2x3) 2.54 ICSP Header (optional) | 1 | H1 |
| 5P-2.54 Header | 2 | H3,H4 |
| Switch 12x12 & Round Button Cover | 2 | KEY1,KEY2 |
| 4.7uH 3015 | 1 | L1 |
| 5161BY Seven Segment Digit | 5 | LED1-LED5 |
| 0805 LED red | 2 | LED6,LED8 |
| 0805 LED green | 1 | LED7 |
| MMBT2222A | 3 | Q1-Q3 |
| 976k | 1 | R1 |
| 309k | 1 | R2 |
| 10k | 3 | R3,R9,R10 |
| 220r | 3 | R4,R12,R14 |
| 1k | 1 | R5,R11,R13 |
| 33r | 1 | R6 |
| 1.2k | 1 | R7 |
| 680r | 1 | R8 |
| SKF14L3 | 1 | SW1 |
| Switch SMD 3x6 | 1 | SW2 |
| MCP1640CT SOT-23-6 | 1 | U1 |
| ATmega328P | 1 | U2 |
| TM1637 | 1 | U3 |
| 8Mhz/16Mhz 3225 crystal | 1 | X1 |


***
# ELECTRIC COMPONENTS - MAIN BOARD V2 CIRCUIT:
| Component | Amount | Silkscreen label |
|:----------|:------:|-----------------:|
| BH-AA-A5BJ012 | 1 | B1,B2 |
| Passive Buzzer 12x9.5 | 1 | BUZ1 |
| 22uF | 2 | C1,C2 |
| 100nF | 6 | C3-C5,C10-C12 |
| 22pF | 2 | C6,C7 |
| 10uF | 1 | C8 |
| 1uF | 1 | C9 |
| 100pF | 2 | C13,C14 |
| SS34 | 1 | D1 |
| 6P (2x3) 2.54 ICSP Header (optional) | 1 | H1 |
| 5P-2.54 Header | 2 | H3,H4 |
| Switch 12x12 & Round Button Cover | 2 | KEY1,KEY2 |
| 22uH | 1 | L1 |
| 5161BY Seven Segment Digit | 5 | LED1-LED5 |
| 0805 LED red | 2 | LED6,LED8 |
| 0805 LED green | 1 | LED7 |
| MMBT2222A | 3 | Q1-Q3 |
| 220k | 1 | R1 |
| 30k | 1 | R2 |
| 10k | 3 | R3,R9,R10 |
| 220r | 3 | R4,R12,R14 |
| 1k | 1 | R5,R11,R13 |
| 33r | 1 | R6 |
| 1.2k | 1 | R7 |
| 680r | 1 | R8 |
| SKF14L3 | 1 | SW1 |
| Switch SMD 3x6 | 1 | SW2 |
| MT3608 | 1 | U1 |
| ATmega328P | 1 | U2 |
| TM1637 | 1 | U3 |
| 8Mhz/16Mhz 3225 crystal | 1 | X1 |


***
# Housing Components:
| Component | Amount |
|:----------|-------:|
| M3 Threaded Heat Insert: 5x4,2mm (height x outer diameter) | 8 |
| M3x6mm | 2 |
| M3x18mm | 3 |
| M3x20mm | 3 |
| M3 Threaded Heat Insert: 3x4,2mm (height x outer diameter) | 1 |
| M3x4mm | 1 |
| AA Battery | 2 |


***
# GALLERY
![Schematic HV Circuit](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/Schematic_GeigerMuellerTube_V2.png)
_Schematic of the high voltage PCB_  
![Schematic MainBoard](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/Schematic_GeigerMuellerMainBoard_V2.png)
_Schematic of the main board (V2)_  
![Complete Geiger Counter](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/GeigerCounterComplete.jpg)
_Complete Geiger Counter Build_  
![Housing](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/Housing.jpg)
_3D printed housing_  

***
# NAVIGATION
The Geiger counter is controlled with two buttons. The **lower button** cycles through the measurement modes: µS/h (microsieverts per hour), cpm (counts per minute), and total counts. The **upper button** resets the counts to zero, which also restarts the µS/h and cpm readings. Holding down the **upper button** takes you into the settings menu. Once inside, the **lower button** cycles through the available options, while the **upper button** changes the selected setting. A long press exits the menu and returns to the main display.  
The configurable options include battery type (Alkaline, NiMH, or Lithium), sound (On or Off), and LED indicators (On or Off — the warning LED always remains on). All settings are saved in EEPROM, so they remain even after the counter is powered off.  

![Geiger Counter](https://github.com/KonradWohlfahrt/GeigerCounter/blob/main/img/Cover_2.jpg)