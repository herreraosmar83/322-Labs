#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    unsigned int address; 
    unsigned int offset; 
	unsigned int pageNumber; 
    address = atoi(argv[1]);
    pageNumber = address/ 4096;
    offset = address % 4096;

	printf("The address %d contains:\n", address);
	printf("page number = %d\n", pageNumber);
	printf("offset = %d\n", offset);
	
	return 0;
}