CC = gcc

INC = /usr/include/


OUTPUTFILE = BetterShell
OBJS = src/main.c shellFunctions.o fatSupport.o workingDirectory.o root.o pfe.o pbs.o

$(OUTPUTFILE): $(OBJS)
	$(CC) -o $@ $^

shellFunctions.o : lib/shellFunctions.h lib/shellFunctions.c
	$(CC) -c lib/shellFunctions.h lib/shellFunctions.c

fatSupport.o : lib/fatSupport.h lib/fatSupport.c
	$(CC) -c lib/fatSupport.h lib/fatSupport.c

workingDirectory.o : lib/workingDirectory.h lib/workingDirectory.c
	$(CC) -c lib/workingDirectory.h lib/workingDirectory.c

root.o : lib/fat.h lib/fat.c
	$(CC) -c lib/fat.h lib/fat.c

pfe.o : lib/pfe.h lib/pfe.c
	$(CC) -c lib/pfe.h lib/pfe.c

pbs.o : lib/pbs.h lib/pbs.c
	$(CC) -c lib/pbs.h lib/pbs.c

clean :
	rm shellFunctions.o fatSupport.o workingDirectory.o root.o pfe.o pbs.o
