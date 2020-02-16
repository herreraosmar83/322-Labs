#include<stdio.h>  
#include<conio.h>  
#include<io.h>  
#include<string.h>  
#include<stdlib.h> 
#include <sys/stat.h>
#include <fcntl.h>

void output();
int format();
// bool format();
char *or[];
char as[];
int dec[];
char parity[1][1];
char er[1][1];
//main to take in values from command line
int main(int args,char *argv[]){
    char buffer[1024];
   //call format to check for correctness of input
    int formatV = format(args);
   //if format is return false exit
    if(formatV == 0){
        printf("format of input does not meet requirements!");
        exit(0);
    }
    //read in file
    if(formatV == 2){
        ///read file and input each into string
        printf("file detected");
    //     int op = open(argv[1], O_RDWR);
    //     read(op, buffer, sizeof(buffer));
    // // printf("reader\n");
    // //     printf(reader);
    //     close(0);

    }
    
    //filter txt file or stdin to accomadate reequirements



    // do conversions to ascii and other values

    //place values of each byte into rightful index of global values
    printf("test of values \n ");
    printf(argv[0]);
    printf("\n");
    printf(argv[1]);
    for(int i=1;i<=args;i++){
        or[i] = argv[i];
    }
    //call print function
     printf("test of values \n ");
    printf(or[1]);
    printf("\n");
    printf(or[2]);
    printf("\n number of args %d \n",args);

    output(args); 
    




    
}
void output(int args){

//Original ASCII Decimal Parity T.Error
// or[0] = 123;
// as[0] = 321;
// dec[0] = 95;
// parity[0][0] = "evem";
// er[0][0] = "FALSE";
//     printf("\n Original   ASCII   Decimal   Parity   T.Error \n ");
//     printf("---------   -----   -------   ------   ------- \n");
//     printf(" %d         %d      %d        %s     %s",or[0],as[0],dec[0],parity[0][0],er[0][0]);
    printf("\n Original   ASCII   Decimal   Parity   T.Error \n ");
    printf("---------   -----   -------   ------   ------- \n");
    for(int i=1;i<args;i++){    
        printf(" %s         test      test        test     test \n",or[i]);
    }
}

int format(int args){
    //no input
    if(args<=1){
        printf("no value was entered");\
        return 0;
    }
    //assumes input will be in file format
    if(args == 2){
        return 2;
    }
    //input from command line
    if(args > 2){
        return 1;
    }
    
    // two or more inputs suggests pointing to a file or stdin

    return 1;
}