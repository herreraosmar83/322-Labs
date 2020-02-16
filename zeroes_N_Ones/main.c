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
char *parity[];
char *er[];
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
        int opener;
        int rd;
        char *bp[];
        ///read file and input each into string
        printf("file detected");
        opener = open(argv[1], O_RDONLY);
        printf ("Printing %s\n",argv[1]);
        bp = read(opener, buffer, sizeof(buffer));
        printf(bp[0]);
    // printf("reader\n");
    //     printf(reader);
        close(0);

    }
    
    //filter txt file or stdin to accomadate reequirements
        //attempt to check each length of index to add zeroes at the end
        printf(argv[1]);
        //char ts[] = argv[1];
        //printf(ts);  
        // while(sizeof(argv[i]!=7)){
        
        // }
        //if beginning of each index has a zero then ignore or convert to 0


    //place values of each byte into rightful index of global values

    printf("\n ==============================");
    for(int i=1;i<=args;i++ ){
        or[i] = argv[i];
    }
    //call print function
    printf("\n number of args %d \n",args);

    output(args); 
    




    
}
void output(int args){

//Original ASCII Decimal Parity T.Error

    printf("\n Original   ASCII   Decimal   Parity   T.Error \n ");
    printf("---------   -----   -------   ------   ------- \n");
    for(int i=1;i<args;i++){
        //if one's in index add up to odd 
        char *val = "true";
        char *ex = "odd";
        char *data = or[i];
        char c = strtol(data, 0, 2);   
        printf(" %s         %c      %d        %s     %s \n",data,c,c,val,ex);
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
        printf("file foprmat");
        return 2;
    }
    //input from command line
    if(args > 2){
        return 1;
    }
    
    // two or more inputs suggests pointing to a file or stdin

    return 1;
}