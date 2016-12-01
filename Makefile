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
OBJS = fatSupport.o fat.o shared.o
SHARE = src/helper/fatSupport.* src/helper/fat.* src/helper/shared.*

$(EXE): $(OBJS) src/main.c
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) -c $^

fatSupport.o: src/helper/fatSupport.h src/helper/fatSupport.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

fat.o: src/helper/fat.h src/helper/fat.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

shared.o: src/helper/shared.h src/helper/shared.c
#	@make validate-build
	$(CC) -g $(CC_OPTIONS) -c $^

bin/cat: src/cmd/cat.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/cd: src/cmd/cd.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/df: src/cmd/df.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/ls: src/cmd/ls.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/mkdir: src/cmd/mkdir.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

bin/pbs: src/cmd/pbs.c $(SHARE)
#	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

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
	rm -f *.o *~ bin/*.o bin/*~ src/*~ src/cmd/*~ src/helper/*~

validate-build:
	if ! [ -d "./bin" ]; then mkdir -p "./bin"; fi
