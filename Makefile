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
MAIN = src/helper/fatSupport.[ch] src/helper/fat.[ch] src/helper/shared.[ch] src/helper/shellFunctions.[ch]
SHARE = src/helper/fatSupport.[ch] src/helper/fat.[ch] src/helper/shared.[ch]

all:
	@make $(EXE)
	@make cat
	@make cd
	@make df
	@make ls
	@make mkdir

$(EXE): src/main.c $(MAIN)
	@make validate-build
	$(CC) -g -o $@ $(CC_OPTIONS) $^

cat: src/cmd/cat.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

cd: src/cmd/cd.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

df: src/cmd/df.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

ls: src/cmd/ls.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

mkdir: src/cmd/mkdir.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

pbs: src/cmd/pbs.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

pfe: src/cmd/pfe.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

pwd: src/cmd/pwd.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

rm: src/cmd/rm.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

rmdir: src/cmd/rmdir.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

touch: src/cmd/touch.c $(SHARE)
	$(CC) -g -o bin/$@ $(CC_OPTIONS) $^

all:
	@make BetterShell
	@make cat
	@make cd
	@make df
	@make ls
	@make mkdir
	@make pbs
	@make pfe
	@make pwd
	@make rm
	@make rmdir
	@make touch
	@make mkdir
	@make clean

clean:
	rm -f *.o *~ bin/*.o bin/*~ src/*~ src/cmd/*~ src/helper/*~ src/helper/*.gch

reset:
	@make clean
	rm -f bin/* BetterShell

validate-build:
	if ! [ -d "./bin" ]; then mkdir -p "./bin"; fi
