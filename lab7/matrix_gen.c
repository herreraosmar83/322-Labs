#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char* argv[]){
    int holder = argc; //prevent error

	int Size = atoi(argv[1]);	//size of matrix

	srand(time(NULL));
	for(int i = 0; i < Size; i++){
		for(int k = 0; k < Size; k++)

			printf("%d ", ((rand() % 201)- 100));
	}
	return 0;
}
//I dont know what im doing :(