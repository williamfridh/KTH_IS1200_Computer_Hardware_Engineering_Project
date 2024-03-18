# KTH_IS1200_Computer_Hardware_Engineering_Project
## X-Pong (passed as an advanced project)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)

**X-Pong is an interpretation of the classic game Pong written in the languages C and Assembly to be run on a pic32 board together with a basic I/O shield. The project was one of the final parts of the KTH course [IS1200 VT23 Computer Hardware Engineering](https://www.kth.se/student/kurser/kurs/IS1200).**

### Configuration
The program comes preconfigured for the hardware given for the course. Only the Makefile should be reconfigured for compiling, anything else can cause errors.

### Compiling & Installation
*Note that these steps are just general instructions. They may vary depending on your system.*

To compile the code, you need the following:
* The files (download via the button above)
* MCB32 toolchain (available on the course page)
* A pic32 board connected to the computer via USB

Now, you simply have to enter the MCB32 environment, navigate to the folder and execute the following commands:

The first command is for compiling the code. Here, you'll see if you got any errors:
```
make;
```

The second command will install the compiled files on the chip kit:
```
make install;
```

Now, unless you got any errors, the code should be sent to the pic32.

### Required Files
All files except for the following are required for compiling:
* .gitignore
* README.md
* readme.txt

### A list of known bugs
* The ball can get stuck on the edge and start vibrating while still moving horizontally.
* The ball can get in a fixed angle at the top and bottom (it keeps going back and fort horizontally).
* Random highscore (slot 9) after first insertion. Dissapear when more is added.
* Pressing OK when starting the game results in moving right paddle.

### Credits & Acknowledgments
* Fridh, William (https://github.com/williamfridh)
* Åhlin, Pontus (https://github.com/PontusAhlin)

