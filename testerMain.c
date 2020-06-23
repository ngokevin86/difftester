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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define DEBUG 0

int main(int argc, char* argv[]){
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
		printf("Error: program '%s' does not exist in directory.\n", argv[argCount]);
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

	printf("Going to execute: ");
	for(int i = 0; i < argc - 1; i++){
		printf("%s ", argExec[i]);
	}
	printf("\n");

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
		/*
		if -f flag is set
			argDiff[2] = argv[3]
		else
			argDiff[2] = "output.txt"
		*/
		argDiff[2] = "output.txt";
		argDiff[3] = NULL;
		printf(">>>>Diffing between output from '%s' and output.txt...\n", argv[argCount]);
		if((execvp(argDiff[0], argDiff)) == -1){
			fprintf(stderr, "Error exec in parent: %s\n", strerror(errno));
			exit(errno);
		}
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
		if((dup2(fdWrite, 1)) == -1){	//set stdout to pipe
			fprintf(stderr, "Error dup2 (stdout) in child: %s\n", strerror(errno));
			exit(errno);
		}
		if((dup2(fdWrite, 2)) == -1){	//set stderr to pipe
			fprintf(stderr, "Error dup2 (stderr) in child: %s\n", strerror(errno));
			exit(errno);
		}
		if((execvp(argExec[0], argExec)) == -1){
			fprintf(stderr, "Error exec in child: %s\n", strerror(errno));
			exit(errno);
		}
		close(fdWrite);
	}
	return 0;
}
