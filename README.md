# PIO-Beispiel

Example to build a trafficlight control with Raspberry Pi Pico and its PIO hardware

You may copy the directory structure to your own system and adapt the PDK-SDK-PATH to the CMake-files.
Then whinin PIOBeispiel you may just call cmake . && make

The Example Circuit assumes there is a
white  LED on GPIO17   ; can be left out, it just signals new red phase in the unoptimized version. 
                       ; in the optimized version it signals red and green phases
                       
red    LED on GPIO18

yellow LED on GPIO19

green  LED on GPIO20


I am using 220 Ohm resistors for the LEDs

The Out-Mapping is defined as {GPIO17, GPIO18, GPIO19, GPIO20}
The OSR (Output-Shift-Register stores the patterns for the phases red, red-yellow, green, yellow 
Its 4 bit shifts control the LEDs accordingly

In the PIO state machine the OSR conducts right shifts 
