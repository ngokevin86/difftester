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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define DEBUG 1

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

	int argCount = 1;	//position of program argument in argv

	if(strncmp(argv[1], "-f", 2) == 0){	//if receives -f flag and has at least 3 supplied arguments
		if(argc < 4){	//needs at least a program argument
			printf("Usage with -f: './tester -f <output.txt> <program> <arg1>\n");
			return 1;
		}
		if(DEBUG)printf("received '-f' as arg 2\n");
		argCount += 2;	//move position of argument
		return 0;	//temporary
	}

	if(access(argv[argCount], F_OK) == -1){	//if program doesn't exist
		printf("Error: program '%s' does not exist in current directory.\n", argv[argCount]);
		return 1;
	}

	if(access("output.txt", F_OK) != 0){	//if diff file doesn't exist
		printf("Error: expected file 'output.txt' not found.\n");
		return 1;
	}
	char* argExec[argc];

	char* result;	//prepend "./" to the program name
	if((result = malloc(strlen(argv[argCount]) + 3)) == NULL){
		fprintf(stderr, "Error while mallocing: %s\n", strerror(errno));
		exit(errno);
	}
	strcpy(result, "./");
	strcat(result, argv[argCount]);
	argExec[0] = result;

	for(int i = argCount + 1; i < argc; i++){
		argExec[i - argCount] = argv[i];
	}
	argExec[argc - 1] = NULL;

	if(DEBUG){
		for(int i = 0; i < argc; i++){
			printf("argExec: %s\n", argExec[i]);
		}
	}

	//create pipe
	int fd[2];
	if(pipe(fd) < 0){
		fprintf(stderr, "Error while piping: %s\n", strerror(errno));
		exit(errno);
	}
	int fdRead = fd[0];
	int fdWrite = fd[1];

	//fork and exec
	if(fork()){	//parent
		wait(NULL);
		free(result);	//free malloc
		if(DEBUG)printf("Parent start\n");
		if((close(fdWrite)) == -1){	//close unneeded write pipe
			fprintf(stderr, "Error closing write pipe: %s\n", strerror(errno));
			exit(errno);
		}

		if(access(".temp.txt", F_OK) == 0){	//remove if temp file exists
			if(remove(".temp.txt") != 0){	//if error while removing temp file
				fprintf(stderr, "Error while removing '.temp.txt': %s\n", strerror(errno));
				exit(errno);
			}
		}
		FILE *temp = fopen(".temp.txt", "w+");	//create + open file '.temp.txt' to write to
		char buffer[1];
		while(read(fdRead, buffer, sizeof(buffer)) != 0){
			if(DEBUG)printf("Buf: %s\n", buffer);
			fwrite(buffer, 1, sizeof(buffer), temp);
		}
		fclose(temp);

		char* argDiff[3];
		argDiff[0] = "diff";
		argDiff[1] = ".temp.txt";
		argDiff[2] = "output.txt";
		argDiff[3] = NULL;
		execvp(argDiff[0], argDiff);
	}
	else if(errno != 0){	//error
		fprintf(stderr, "Error while forking: %s\n", strerror(errno));
		exit(errno);
	}
	else{	//child
		if(DEBUG)printf("Child start\n");
		if((close(fdRead)) == -1){	//close unneeded read pipe
			fprintf(stderr, "Error closing read pipe: %s\n", strerror(errno));
			exit(errno);
		}
		//point stdout to pipe
		if((dup2(fdWrite, 1)) == -1){
			fprintf(stderr, "Error dup2 (stdout) in child: %s\n", strerror(errno));
			exit(errno);
		}
		/*if((dup2(fdWrite, 2)) == -1){
			fprintf(stderr, "Error dup2 (stderr) in child: %s\n", strerror(errno));
			exit(errno);
		}*/
		
		//exec program
		//argExec[] = {argv[argCount], argv[argCount + 1], argv[argCount + 2], NULL};	//NULL needs to be last argument
		//needs to be dynamic dependent on how many arguments are supplied
		//which is more important when there are more than just 5 arguments
		//although a program that takes more than five arguments would just be insane
		if((execvp(argExec[0], argExec)) == -1){
			fprintf(stderr, "Error exec in child: %s\n", strerror(errno));
			exit(errno);
		}
		close(fdWrite);
	}
	return 0;
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