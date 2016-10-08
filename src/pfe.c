#include <fatSupport.c>

int checkRange(int x, int y){
	if(x>y){
		printf("Error: x > y\n");
		return 1;
	} else if(x<2){
		printf("Error: x < 2\n");
		return 1;
	} else {
		return 0;
	}

}

char* readFAT12Table(int fatTable){
	unsigned char* fat;

	fat = malloc(2 * (BYTES_PER_SECTOR * sizeof(unsigned char)));

	int i, br = 0;
	for(i=1; i<3; i++){
		br = br + readSector(i, fat[i*BYTES_PER_SECTOR]);
	}
	return fat;
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

	if(checkRange(x, y) == 1) { printf("checkRange Failed"); }
	else {
		printf("Range ok");	
	}

	readFAT12Table(1);

	return(0);
}
