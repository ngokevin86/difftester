Kevin Ngo
Diff Tester

Included files:
testerMain.c
Makefile

Idea of the program:
This program allows you to to be able to quickly execute and compare the output of a program using system diff.
The program creates a temporary file named '.temp.txt', and then compares it to an expected text file named 'output.txt'.
Alternatively you can use the '-f' flag and supply a text file to compare the output to instead of 'output.txt'.

To compile, have required files
	testerMain.c
	Makefile
in the same directory, and use the command
	make
OR
	gcc -o tester testerMain.c
to compile 'testerMain.c'

To run, use the command format
	./testerMain <program> <arguments>
where
	<program>
	is your compiled program to run
and
	<arguments>
	is the arguments to given to your program
With this format, it will expect a file named
	output.txt
in the current directory, and will take up to 8 arguments.

ALTERNATIVELY to run, use the command format
	./testerMain -f <output.txt> <program> <arguments>
where
	<output.txt>
	is a given text file to compare to at the end
This will take up to 6 arguments.

Output from this program is a hidden temp file named '.temp.txt'.
This file is used for the diff function.

Example command:
	./tester addNum 8 6
where 'addNum' is a program which adds two numbers together.

Example command with '-f' flag:
	./tester -f test.txt addNum 8 6
where 'test.txt' is a text file.