This project explains how you can transform a Bittle to a Bumblebee transformer.

<img width="278" height="305" alt="image" src="https://github.com/user-attachments/assets/e96e8863-0571-474b-8d78-460558ad8c35" />
<img width="337" height="240" alt="image" src="https://github.com/user-attachments/assets/00a8004b-55b7-417e-ab83-fd946f8ed8d0" />



This project contains different folders for the code, hardware and concept for a UI interface to control the transformer.


Code: contains all the code needed to convert your Bittle to a transformer.

Print_Files(STL): contains printable files needed to aesthetically change your Bittle.

Solidworks_Files: contains editable Solidworks files of the printable stl parts.


To convert your Bittle robot to a transformer you first need to download and 3d print all the STL files. The front legs of the Bittle need to be removed and swapped out for the given files. On the back legs, a servo has to be installed geared to the wheels.
To be able to drive these servo's, an Arduino needs to be mounted on top of the original board. Part "pcb holder" lets you mount the Arduino with Grove shield on top of the BiBoard V1. Code "Bittle_transform.ino" needs to be flashed to the Arduino and the given sensors need to be installed on the corresponding pins. Connect the serial port of the Arduino to the serial port of the Bittle.
The Arduino will send commands to the Bittle once the button is pressed. The Bittle now needs to listen to the these commands. To install the commands, "OpenCatEsp32" needs to be downloaded and unzipped. Flash this code to the Bittle and send "XS" as a serial command. https://docs.petoi.com/arduino-ide/upload-sketch-for-biboard


Now you can install the panels, press the button and your Bittle should transform from a car to a transformer.
