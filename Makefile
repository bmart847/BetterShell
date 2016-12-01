#   Author: Bryan Martin and Joseph Listro
#   Class:  CSI 385 <Section 02>
#   Assignment: Semester Project
#   Date Assigned: 6 September 2016
#   Due Date: 6 December 2016
	
#   Description:  Project Makefile
	
#   Certification of Authenticity:
#	   I certify that this assignment is entirely my own work.

CC         = gcc
CC_OPTIONS = -std=c99 -D _SVID_SOURCE



EXE = BetterShell
# PROGS = bin/cat bin/cd bin/df bin/cat bin/cd bin/df bin/ls bin/mkdir bin/pbs
OBJS = fatSupport.o fat.o shared.o shellFunctions.o
SHARE = src/helper/fatSupport.* src/helper/fat.* src/helper/shared.*

$(EXE): src/main.c $(OBJS)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

fatSupport.o: src/helper/fatSupport.h src/helper/fatSupport.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

fat.o: src/helper/fat.h src/helper/fat.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

shared.o: src/helper/shared.h src/helper/shared.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

shellFunctions.o: src/helper/shellFunctions.h src/helper/shellFunctions.c
	$(CC) -g $(CC_OPTIONS) -c $^

cat: src/cmd/cat.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

cd: src/cmd/cd.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

df: src/cmd/df.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

ls: src/cmd/ls.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

mkdir: src/cmd/mkdir.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

pbs: src/cmd/pbs.c $(SHARE)
#	@make validate-build
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

bin/pfe: src/cmd/pfe.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/pwd: src/cmd/pwd.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/rm: src/cmd/rm.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/rmdir: src/cmd/rmdir.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/touch: src/cmd/touch.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

run:
	@make all

clean:
	rm -f *.o *~ bin/*.o bin/*~ src/*~ src/cmd/*~ src/helper/*~ src/helper/*.gch

validate-build:
	if ! [ -d "./bin" ]; then mkdir -p "./bin"; fi
