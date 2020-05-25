/* Kevin Ngo
 * C Tester
 */

/*
	This program will run expecting either potentially one or no arguments.

	If there are no arguments, then it will by default look for a specifically named textfile
	named "input.txt" which will contain the exact comamnd to run.

	There are optional input flags which will control what other functions to run

	-g
	generates makefile

	-

	

 */


#include <stdio.h>

int main(int argc, char* argv[]){

	//idea:
	//be able to shortcut rerunning programs for testing.

	/*
	iteration one: just generate the makefile?
		take program file name to generate

	iteration two: read command from specific textfile
		user defined textfile with input command which program will read and execute directly

	iteration three: pipe output to a file
		self explanitory, goes into "output.txt"

	iteration four: diff given output and expected output
	
	*/

	if(argc == 1){
		//check for makefile
		//check for program
		//check for command textfile
		//run command in textfile
	}

	//check input
	if(argc > 2){	//no more than executable and potentially one flag
		printf("Usage: './tester <-flag>'\n");
		printf("Flags:\n");
		printf("'-g': Generate Makefile\n");
	}

	//check argv[2]


	printf("Usage: './tester <-flag>'\n");
	printf("Flags: \n");
	printf("'-g': Generate Makefile\n");

	return 1;
}