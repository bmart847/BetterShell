#   Author: Bryan Martin and Joseph Listro
#   Class:  CSI 385 <Section 02>
#   Assignment: Semester Project
#   Date Assigned: 6 September 2016
#   Due Date: 6 December 2016
	
#   Description:  Prints the current working directory.
	
#   Certification of Authenticity:
#	   I certify that this assignment is entirely my own work.

CC         = gcc
CC_OPTIONS = -std=c99 -D _SVID_SOURCE

EXE  = bin/cat bin/cd bin/df bin/ls bin/mkdir bin/pbs bin/pfe bin/pwd bin/rm bin/rmdir bin/touch bin/BetterShell
OBJS = bin/cat.o bin/cd.o bin/df.o bin/ls.o bin/mkdir.o bin/pbs.o bin/pfe.o bin/pwd.o bin/rm.o bin/rmdir.o bin/touch.o bin/fatSupport.o bin/fat.o bin/workingDirectory.o

all: $(EXE)
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/fatSupport.o: src/helper/fatSupport.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/fat.o: src/helper/fat.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/shared.o: src/helper/shared.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/cat.o: src/cmd/cat.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/cd.o: src/cmd/cd.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/df.o: src/cmd/df.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/ls.o: src/cmd/ls.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/mkdir.o: src/cmd/mkdir.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/pbs.o: src/cmd/pbs.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/pfe.o: src/cmd/pfe.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/pwd.o: src/cmd/pwd.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/rm.o: src/cmd/rm.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/rmdir.o: src/cmd/rmdir.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/touch.o: src/cmd/touch.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/cat.o: src/cmd/cat.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/betterShell.o: src/helper/shellFunctions.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/main.o: src/main.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

bin/BetterShell: bin/betterShell.o bin/main.o
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

run:
	@make all

clean:
	rm -f *.o *~ bin/*.o bin/*~ src/*~ src/cmd/*~ src/helper/*~

validate-build:
	if ! [ -d "./bin" ]; then mkdir -p "./bin"; fi
