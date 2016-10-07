#include "fatSupport.h"
#include "fatSupport.c"

bool checkRange(int x, int y){
	if(x>y){
		printf("Error: x > y\n");
		return false;
	} else if(x<2){
		printf{"Error: x < 2\n");
		return false;
	} else {
		return true;
	}

}

char* readFAT12Table(int fatTable){
	read_sector(0,


}


int main(int argc, char*argv[]){
	int x, y;

        if(argc < 3){
                printf("Too few arguments.\n");
                return(1);
        } else if (argc > 3){
                printf("Too many arguments.\n");
                return(1);
        }
        else {
        /* Read arguments */
                x = atoi(argv[1]);
                y = atoi(argv[2]);
        }

	if(checkRange(x, y) == false) { printf("checkRange Failed"); }
	else {

		printf("Range ok");
		
	}

	return(0);
}
