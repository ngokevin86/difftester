/* Kevin Ngo
 * C Tester
 */

/*
	This program will run expecting at least one argument - the program to test to.

	Up to an additional 3 arguments may be supplied as arguments to be given to the program being tested.

	The program will take the output from the tested program and put it in a temp file, and then diff it against
	an expected "output.txt" file (which should exist in the same directory).

	The idea is to allow repeated running via Make tests

	[To be added]
	A flag to allow diff against another text file (something other than output.txt)
	-f <file.txt>
	where 'file.txt' is the file which it will diff the output to.

	-g
	just generate a Makefile

 */


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

//int makegen();

int main(int argc, char* argv[]){
	/* 
	Take in some number of arguments, with the first given argument being the name of the program executable
	Execute the given program as given, just that it will pipe the output of that program to a .temp.txt file and then
	at the end, diff that file and an expected output.txt
	
	Expected input
	./tester <program> <arg1> <arg2> <arg3>...

	-?later be able to give it a specific text file to compare against?
		something like
		./tester -f <textfile> <program> <arg1> <arg2> <arg3>...
	*/

	//check input
	if(argc < 2 || argc > 5){
		printf("Usage: './tester <program> <arg1> <arg2> <arg3>'\n");
		return 1;
	}

	//-later- check flag
	//if flag is set, change what program will take in as the input program
	//check argv[2]
	if(strncmp(argv[2], "-f", 2) == 0){
		if(makegen()){
			return 1;
		}
		return 0;
	}
	else{	//arg 2 is the program

	}

	int argCount = 2;	//program argument, arguments 1, 2, and 3 are +1, +2, and +3 respectively

	if(access(argv[argCount], F_OK) == -1){	//if 
		printf("Error: program '%s' does not exist in current directory.\n", argv[argCounter]);
		return 1;
	}

	if(access("output.txt", F_OK) != 1){
		printf("Error: expected file 'output.txt' not found.\n");
	}


	//Possibility 1: Defined structure
	/*
	Input struct:
	string program name
	type arg1
	type arg2
	type arg3
	*/
	//?End goal: Dynamic structure

	//fork and exec
	int err = 0;
	err = fork();
	if(err == 0){	//child
		//point stdout to pipe
		//exec program
		//args[] = {argv[argCount], argv[argCount + 1], argv[argCount + 2], NULL};	//NULL needs to be last argument
		//needs to be dynamic dependent on how many arguments are supplied
		//which is more important when there are more than just 5 arguments
		//although a program that takes more than five arguments would just be insane
		//execvp(argv[argCount], args)

	}
	else if(err == -1){	//error
		fprintf("Error while forking: %s\n", strerror(errno));
		return errno;
	}
	else{	//parent
		//open file '.temp.txt'
		//point pipe to file
		//?also print whatever was in pipe?
		//pipe stdout output to a file named '.temp.txt'

	}

	//exec diff with '.temp.txt' and 'output.txt'

	printf("Usage: './tester <program> <arg1> <arg2> <arg3>'\n");

	return 1;
}

/*

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

	
	//alternatively I should just make it use dollar replacement, which means all, run, and clean will be the same between
	//all generated makefiles, with only the line with the replacement being different
	//--probably just add this later as a refactorization



	return 0;
}*/