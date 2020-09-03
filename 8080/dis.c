#include <stdio.h>
#include <stdlib.h>

int main()
{

    int disassemble(unsigned char *data, int programCounter);
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

    int   programCounter = 0; //tracks position of buffer(data)


    int x = 0;
    while(x<fileSize)
    {
        programCounter += disassemble(data, programCounter);
        x++;                          /////whole thing is a test
    }


}

int disassemble(unsigned char *data, int programCounter)
{
    unsigned char *currentOpcode = &data[programCounter];
    int opbytes = 1;
    switch (*currentOpcode)
    {

    case 0x00:
        printf("NOP\n");
        break;
    case 0x01:
        printf("LXI\tB,#0x%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x02:
        printf("STAX\tB\n");
        break;
    case 0x03:
        printf("INX\tB\n");
        break;
    case 0x04:
        printf("INR\tB\n");
        break;
    case 0x05:
        printf("DCR\tB\n");
        break;
    case 0x06:
        printf("MVI\tB,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
    case 0x07:
        printf("RLC\n");
        break;
    case 0x08:
        printf("NOP\n");
        break;
    case 0x09:
        printf("DAD\tB\n");
        break;
    case 0xA:
        printf("LDAX\tB\n");
        break;
    case 0xB:
        printf("DCX\tB\n");
        break;
    case 0xC:
        printf("INR\tC\n");
        break;
    case 0xD:
        printf("DCR\tC\n");
        break;
    case 0xE:
        printf("MVI\tC,#0x%02\n",currentOpcode[0]);
    case 0x10:
        printf("NOP\n");
        break;
    case 0x11:
        printf("LXI\tD,#%02x%02x", currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x12:
        printf("STAX\tD");
        break;
    case 0x13:
        printf("INX\tD");
        break;
    case 0x14:
        printf("INR\tD");
        break;
    case 0x15:
        printf("DCR\tD");
        break;
    case 0x16:
        printf("MVI\tD,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0x17:
        printf("RAL");
        break;
    case 0x18:
        printf("NOP");
        break;
    case 0x19:
        printf("DAD\tD");
        break;
    case 0x1A:
        printf("LDAX\tD");
        break;
    case 0x1B:
        printf("DCX\tD");
        break;
    case 0x1C:
        printf("INR\tE");
        break;
    case 0x1D:
        printf("DCR\tE");
        break;
    case 0x1E:
        printf("MVI\tE,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0x1F:
        printf("RAR");
        break;
    case 0x20:
        printf("NOP");
        break;
    case 0x21:
        printf("LXI\tH,#%02x%02x", currentOpcode[2], currentOpcode[1]);
        opbytes=3;
        break;
    case 0x22:
        printf("SHLD\t,%02x%02x", currentOpcode[2], currentOpcode[1]); //check the formatting of SHLD
        opbytes=3;
        break;
    case 0x23:
        printf("INX\tH");
        break;
    case 0x24:
        printf("INR\tH");
        break;
    case 0x25:
        printf("DCR\tH");
        break;
    case 0x26:
        printf("MVI\tH,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
    case 0x27:
        printf("DAA\n");
        break;
    case 0x28:
        printf("NOP\n");
        break;
    case 0x29:
        printf("DAD\tH\n");
        break;
    //case 0x2A:















    default:
        printf("UNKNOWN Instructions: 0x%02x\n",*currentOpcode);
        break;
    }
    return opbytes;


}

//nmemb
// might not read all the data, if the file shrank-> the file can change in length during size read
// and reading into the buffer
//also fread can fail.
