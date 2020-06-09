/* Kevin Ngo
 * C Tester
 */

/*
	This program will run expecting either potentially one or no arguments.

	If there are no arguments, then it will by default look for a specifically named textfile
	named "input.txt" which will contain the exact command to run.

	There are optional input flags which will control what other functions to run

	-g
	generates makefile

	-m
	make and run

 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>

int makegen();

int main(int argc, char* argv[]){

	/*
	idea:
	be able to shortcut rerunning programs for testing.
	particularly programs which take input upon running it
	i.e. ./sum 5 3
	saves needing to type the same input over and over again, especially if they get long
	including needing to make and run again, as sometimes previous commands get lost in other commands
	so mashing the up arrow takes awhile
	*/

	/*
	./tester -g
	iteration one: just generate the makefile?
		take program file name to generate
		-allow flags such as -math or -pthread?

	./tester
	iteration two: read command from specific textfile
		user defined textfile with input command which program will read and execute directly
		-have a difference between making and running and just running?
		-allow multiple files to be made and compiled?

	part of ./tester
	iteration three: pipe output to a file
		self explanitory, goes into "output.txt"

	part of ./tester
	iteration four: diff given output and expected output
	
	*/

	/* 
	Idea 2:
	Take in some number of arguments, with the first given argument being the program executable (not this program's
	executable)
	Execute the given program as given, just that it will pipe the output of that program to a .temp.txt file and then
	at the end, diff that file and an expected output.txt



	*/

	if(argc == 1){
		//check for makefile
		//?expect makefile to be named "Makefile"
		if(access("Makefile", F_OK) == -1){
			printf("Makefile does not exist in current directory, move one in or generate a new one with './tester -g'.\n");
			return 1;
		}

		//run make

		//continue if no issues

		//check for command textfile
		if(access("command.txt", F_OK) == -1){
			printf("Makefile already exists in current directory, move or remove before running.\n");
			return 1;
		}

		//run command in textfile
	}

	//check input
	if(argc > 2){	//no more than executable and potentially one flag
		printf("Usage: './tester <-flag>'\n");
		printf("Flags:\n");
		printf("'-g': Generate Makefile\n");
	}

	//check argv[2]
	if(strncmp(argv[2], "-g", 2) == 0){
		if(makegen()){
			return 1;
		}
		return 0;
	}

	printf("Usage: './tester <-flag>'\n");
	printf("Flags: \n");
	printf("'-g': Generate Makefile\n");

	return 1;
}

int makegen(){
	//make sure makefile doesn't already exist
	if(access("Makefile", F_OK) != -1){
		printf("Makefile already exists in current directory, move or remove before running.\n");
		return 1;
	}

	//prompt user for file name
	//?prompt user for executable name
	printf("Enter the name of the program to be compiled (do not include the '.c' file extension):\n");
	//read input
		//perhaps cap the amount of input, and put in a placeholder instead so user can modify it themselves?

	//create file "Makefile"


	//write commented header followed by makefile commands
	//something like

	//#<program name> Makefile
	//all: <program name>.c
	//	gcc -o <program name> <program name.c>
	//run: <program name>
	//	./<program name>
	//clean:
	//	rm -f <program name> *.o

	/*
	alternatively I should just make it use dollar replacement, which means all, run, and clean will be the same between
	all generated makefiles, with only the line with the replacement being different
	--probably just add this later as a refactorization
	*/



	return 0;
}