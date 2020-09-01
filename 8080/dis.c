#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
//read in File name
    printf("Enter the name of the File you want to disassemble:\n");
    char fileName[50];
    fgets(fileName, 50, stdin);
    fileName[strcspn(fileName, "\n")] = 0;

//Open file

    FILE *fp = fopen(fileName, "rb");
    if(fp == NULL)
    {
        printf("Could not file name %s\n", fileName);
        printf("Ending Program\n");
        exit(-1);
    }

//getting the size of the File

    fseek(fp,0L,SEEK_END); //set the 'cursor' at the end of file
    long int fileSize = ftell(fp); // get size of file in bytes(since open in binary mode)
    if(fileSize == -1L)
    {
        printf("Failure to read in size of file into memory/n");
        printf("Ending Program\n");;
        exit(-1);
    }
    fseek(fp,0L,SEEK_SET); //set the 'cursor' back to start


//reading the data inside file into memory
    unsigned char *data = (char*) malloc(fileSize*sizeof(char)); //create memory for array for data to be read into
    fread(data, fileSize,1,fp); //read data into *data malloced array;
    fclose(fp); // close the file



    int x = 0;
    while(x<fileSize){
        printf("%02x\n",data[x]);
        x++;                          /////whole thing is a test
    }




}

//nmemb
// might not read all the data, if the file shrank-> the file can change in length during size read
// and reading into the buffer
//also fread can fail.
