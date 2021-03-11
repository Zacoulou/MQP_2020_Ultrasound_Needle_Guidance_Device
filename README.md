# MQP_2020_Ultrasound_Needle_Guidance_Device
By: Isaac Abouaf

Code for portable ultrasound needle guidance device. Runs on an ESP32 mounted to a custom PCB. The device uses a Bournes EMS22A30 encoder to measure the rotation of a mirror in relation to ultrasound imaging, and a directional button for menu navigation for the device. The user can tilt the mirror through a range of angles to view numerous cross sections of an area of interest to gain a wholistic understanding of a region. 

![IMG-4472](https://user-images.githubusercontent.com/46580558/110866370-0a53ce80-8293-11eb-8faf-0d9d28ca2039.JPG)


## Software
User can navigate between multiple pages using the directional button and select which operation to perform. The device is capable of displaying encoder readings in real time, connecting to wifi networks, and updating firmware remotely. The menus are listed below:

#### Main Page
- Orientation Readings
- Perform Sweep
#### Settings Page
- WiFi
  - Reconnect
  - Configure New Network
  - Disconnect
  - Network Details
  - Device Details
- Firmware
  - Update
  - Firmware Details
  - Reset Device
 
![IMG-4476](https://user-images.githubusercontent.com/46580558/110866598-628ad080-8293-11eb-8d95-b26bcce22285.JPG)

## Electrical
The device consists of a directional button, 2.4 inch TFT display, a Bourns EMS22A30 encoder, and an ESP32 microcontroller. The PCB below was designed in Autodesk Eagle and manufactered and shipped from JLCPCB. The components were soldered to the board manually.

![MQP_2020_Circuit_Schematic_2020-Dec-11_12-03-22AM-000_CustomizedView17367344950](https://user-images.githubusercontent.com/46580558/110867504-d8dc0280-8294-11eb-8fcd-7307a1028178.png)


## Mechanical
The mechanical components of the device were designed in Autodesk Fusion 360 and 3D printed in PLA. Two belts are used in conjunction with pulley wheels to achieve a 2:1 ratio for the rotation between the needle and mirror so that they could rotate collinearly, but at different rates. This was crucial for properly aligning the needle with the reflected ultrasound waves, because for every degree the mirror is rotated, the reflected ultrasound waves have an angular difference of 2 degrees.

![IMG-4473](https://user-images.githubusercontent.com/46580558/110866383-1049af80-8293-11eb-9de5-4d90ae4baea9.JPG)




