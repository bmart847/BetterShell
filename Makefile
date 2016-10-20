BetterShell : main.o shellFunctions.o root.o pfe.o pbs.o
	gcc -o BetterShell main.o shellFunctions.o root.o pfe.o pbs.o

main.o : src/main.c
	gcc -c src/main.c

shellFunctions.o : lib/shellFunctions.h lib/shellFunctions.c
	gcc -c lib/shellFunctions.h lib/shellFunctions.c

root.o : lib/root.h lib/root.c
	gcc -c lib/root.h lib/root.c

pfe.o : lib/pfe.h lib/pfe.c
	gcc -c lib/pfe.h lib/pfe.c

pbs.o : lib/pbs.h lib/pbs.c
	gcc -c lib/pbs.h lib/pbs.c
