#include <stdio.h>
int main(int argc, char* argv[]){
	FILE* logfile;
	logfile = fopen("./lab6.log", "a");
	fprintf(logfile,"Pop %s\n", argv[0]);
	fclose(logfile);
	return 0;
}