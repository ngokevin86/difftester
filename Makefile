#Kevin Ngo
#Diff Tester - Makefile

all: testerMain.c
	gcc -o tester testerMain.c

clean:
	rm -f tester *.o