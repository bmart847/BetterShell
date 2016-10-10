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

unsigned char* readFAT12Table(int fatTable){
	unsigned char* fat;

	fat = malloc(9 * (BYTES_PER_SECTOR * sizeof(unsigned char)));

	int i, br = 0;
	if(fatTable == 1) {
		for(i=1; i<10; i++){
			br = br + read_sector(i, fat[i*BYTES_PER_SECTOR]);
		}
		return fat;
	} else if(fatTable == 2) {
		for(i=10; i<20; i++){
			br = br + read_sector(i, fat[i*BYTES_PER_SECTOR]);
                }
		return fat;
	} else {
		free(fat);
		return NULL;
	}
}


int pfe(int arg1, int arg2){
	/*
	int x, y;

        if(argc < 3){
                printf("Too few arguments.\n");
                return(1);
        } else if (argc > 3){
                printf("Too many arguments.\n");
                return(1);
        }

        else {
        * Read arguments *
                x = atoi(argv[1]);
                y = atoi(argv[2]);
        }
	*/

	unsigned char* fat1, fat2;
	if(checkRange(arg1, arg2) == 1) { printf("checkRange Failed"); }
	else {
		printf("Range ok");	
	}

	fat1 = readFAT12Table(1);
	fat2 = readFAT12Table(2);

	printf("Read both FAT Tables\n");

	return(0);
}
