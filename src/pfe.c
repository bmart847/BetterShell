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

	fat = (unsigned char*) malloc(9 * (BYTES_PER_SECTOR * sizeof(unsigned char)));

	int i, br = 0;
	if(fatTable == 1) {
		for(i=1; i<10; i++){
			br = br + read_sector(i, &fat[(i-1)*BYTES_PER_SECTOR]);
		}
		return fat;
	} else if(fatTable == 2) {
		for(i=10; i<19; i++){
			br = br + read_sector(i, &fat[(i-10)*BYTES_PER_SECTOR]);
                }
		return fat;
	} else {
		free(fat);
		return NULL;
	}
}


int pfe(int arg1, int arg2){
	unsigned char* fat1, fat2;
	if(checkRange(arg1, arg2) == 1) { printf("checkRange Failed\n"); }
	else {
		printf("Range ok\n");	
	}

	fat1 = readFAT12Table(1);
	fat2 = readFAT12Table(2);

	printf("Read both FAT Tables\n");

	return(0);
}
