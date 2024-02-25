---------------------------
B2C4Palm 0.1 - Beta Release
by Greg Smith
---------------------------

This is the Beta Release of B2C4Palm.  Please read the following instructions and follow them.  I am avaialable for help here:

AIM: DevCybiko or b2c4Palm
Email: cybiko@alcorgrp.com

1) Read the License Agreement
2) Install B2C4Palm, PalmDev, and Cygwin directories on your C:\ drive.
3) Compile the test programs
   a) build circle
   b) build font
   c) build hello
   d) build key
   e) build rect
   f) build beep
   g) (do not build menu.bld - it is not working)
4) Download the Emulator and ROMs from http://DevCybiko.com/Cybiko/3party/b2c4palm.zip
5) report errors to cybiko@alcorgrp.com or DevCybiko or b2c4palm on AIM

Differences from B2C4Cybiko:
0) b2c4palm uses the C compiler's cpp pre-processor. so all the macro processing capabilities of c are in force
1) comments are just like in C, no longer can you use the apostrophe
   a) /* begins a block of multiline comments
   b) */ ends a block of multiline comments
   c) // begins a single-line comment
2) Include directive has been replaced with #include
3) #define macro works as in C
4) #ifdef works as in C
5) character constants are now identified by apostrophes ('a')
6) penx and peny give the current position of the pen on the palm display. if the pen is not on the display then penx=peny=-1
7) you must call the key variable or key() function to update penx/peny
8) there is no real difference in performance between key and key()

thanks

-greg smith
cybiko@alcorgrp.com
AIM: DevCybiko or b2c4palm