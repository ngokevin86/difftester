#Kevin Ngo
#CTester - Makefile

all: testerMain.c
	gcc -o tester testerMain.c

run: tester
	./tester

clean:
	rm -f tester *.o