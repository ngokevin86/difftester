Kevin Ngo
C Tester

Included files:
testerMain.c
Makefile

Idea of the program:
The primary idea of the program is to be able to quickly rerun a program with input over and over again.
Although you could hit the up arrow in terminal until you get the previous command back, 
sometimes you run a ton of other commands between then, so you're stuck mashing the up arrow a few times.
Alternatively you could retype the command, but they can get long.

Additionally the program should be able to create a (simple) makefile which can be used.


Self notes:
Seems "make" has a fair amount of this functionality already, just it's kinda confusing.
Maybe instead of trying to replicate those functionalities I could just generate a makefile
*shrug*
or I could primarily focus on the makefile generation, and then do the running as a side thing.

I could also have it pipe stdout to a text file which then I diff it to another text file, as I had considered earlier.