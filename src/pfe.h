int checkRange(int x, int y); /* Verifies that the provided integers are acceptable. */
unsigned char* readFAT12Table(int fatTable); /* Reads FAT12 Table and returns either Table 1 or Table 2 */
int pfe(int arg1, int arg2); /* Prints FAT12 Table Entries from (arg1+1) to arg2 */
void pfe_help(); /* Handles Printing Help for pfe */

/* Function Defintions are included below */
#include "pfe.c"
