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
        printf("LXI\tD,#%0x02x%02x\n", currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x12:
        printf("STAX\tD\n");
        break;
    case 0x13:
        printf("INX\tD\n");
        break;
    case 0x14:
        printf("INR\tD\n");
        break;
    case 0x15:
        printf("DCR\tD\n");
        break;
    case 0x16:
        printf("MVI\tD,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0x17:
        printf("RAL\n");
        break;
    case 0x18:
        printf("NOP\n");
        break;
    case 0x19:
        printf("DAD\tD\n");
        break;
    case 0x1A:
        printf("LDAX\tD\n");
        break;
    case 0x1B:
        printf("DCX\tD\n");
        break;
    case 0x1C:
        printf("INR\tE\n");
        break;
    case 0x1D:
        printf("DCR\tE\n");
        break;
    case 0x1E:
        printf("MVI\tE,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0x1F:
        printf("RAR\n");
        break;
    case 0x20:
        printf("NOP\n");
        break;
    case 0x21:
        printf("LXI\tH,#0x%02x%02x\n", currentOpcode[2], currentOpcode[1]);
        opbytes=3;
        break;
    case 0x22:
        printf("SHLD\t,0x%02x%02x\n", currentOpcode[2], currentOpcode[1]); //check the formatting of SHLD
        opbytes=3;
        break;
    case 0x23:
        printf("INX\tH\n");
        break;
    case 0x24:
        printf("INR\tH\n");
        break;
    case 0x25:
        printf("DCR\tH\n");
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
    case 0x2A:
        printf("LHLD\t,0x%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x2B:
        printf("DCX\tH\n");
        break;
    case 0x2C:
        printf("INR\tL\n");
        break;
    case 0x2D:
        printf("DCR\tL\n");
        break;
    case 0x2E:
        printf("MVI\tL,#0x%02\n",currentOpcode[0]);
        opbytes = 2;
        break;
    case 0x2F:
        printf("CMA\t\n");
        break;
    case 0x30:
        printf("NOP\n");
        break;
    case 0x31:
        printf("LXI\tSP,#%0x%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x32:
        printf("STA\t%0x%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x33:
        printf("INX\tSP\n");
        break;
    case 0x34:
        printf("INR\tM\n");
        break;
    case 0x35:
        printf("DCR\tM\n");
        break;
    case 0x36:
        printf("MVI\tM,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
    case 0x37:
        printf("STC\n");
        break;
    case 0x38:
        printf("NOP\n");
        break;
    case 0x39:
        printf("DAD\tSP\n");
        break;
    case 0x3A:
        printf("LDA\t%0x%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        break;
    case 0x3B:
        printf("DCX\tSP\n");
        break;
    case 0x3C:
        printf("INR\tA\n");
        break;
    case 0x3D:
        printf("DCR\tA\n");
        break;
    case 0x3E:
        printf("MVI\tA,#0x%02x\n",currentOpcode[1]);
        opbytes = 2;
    case 0x3F:
        printf("CMC\n");
        break;
    case 0x40:
        printf("MOV\tB,B\n");
        break;
    case 0x41:
        printf("MOV\tB,C\n");
        break;
    case 0x42:
        printf("MOV\tB,D\n");
        break;
    case 0x43:
        printf("MOV\tB,E\n");
        break;
    case 0x44:
        printf("MOV\tB,H\n");
        break;
    case 0x45:
        printf("MOV\tB,L\n");
        break;
    case 0x46:
        printf("MOV\tB,M\n");
        break;
    case 0x47:
        printf("MOV\tB,A\n");
        break;
    case 0x48:
        printf("MOV\tC,B\n");
        break;
    case 0x49:
        printf("MOV\tC,C\n");
        break;
    case 0x4a:
        printf("MOV\tC,D\n");
        break;
    case 0x4B:
        printf("MOV\tC,E\n");
        break;
    case 0x4C:
        printf("MOV\tC,H\n");
        break;
    case 0x4D:
        printf("MOV\tC,L\n");
        break;
    case 0x4E:
        printf("MOV\tC,M\n");
        break;
    case 0x4F:
        printf("MOV\tC,A\n");
        break;
    case 0x50:
        printf("MOV\tD,B\n");
        break;
    case 0x51:
        printf("MOV\tD,C\n");
        break;
    case 0x52:
        printf("MOV\tD,D\n");
        break;
    case 0x53:
        printf("MOV\tD.E\n");
        break;
    case 0x54:
        printf("MOV\tD,H\n");
        break;
    case 0x55:
        printf("MOV\tD,L\n");
        break;
    case 0x56:
        printf("MOV\tD,M\n");
        break;
    case 0x57:
        printf("MOV\tD,A\n");
        break;
    case 0x58:
        printf("MOV\tE,B\n");
        break;
    case 0x59:
        printf("MOV\tE,C\n");
        break;
    case 0x5A:
        printf("MOV\tE,D\n");
        break;
    case 0x5B:
        printf("MOV\tE,E\n");
        break;
    case 0x5C:
        printf("MOV\tE,H\n");
        break;
    case 0x5D:
        printf("MOV\tE,L\n");
        break;
    case 0x5E:
        printf("MOV\tE,M\n");
        break;
    case 0x5F:
        printf("MOV\tE,A\n");
        break;
    case 0x60:
        printf("MOV\tH,B\n");
        break;
    case 0x61:
        printf("MOV\tH,C\n");
        break;
    case 0x62:
        printf("MOV\tH,D\n");
        break;
    case 0x63:
        printf("MOV\tH,E\n");
        break;
    case 0x64:
        printf("MOV\tH,H\n");
        break;
    case 0x65:
        printf("MOV\tH,L\n");
        break;
    case 0x66:
        printf("MOV\tH,M\n");
        break;
    case 0x67:
        printf("MOV\tH,A\n");
        break;
    case 0x68:
        printf("MOV\tL,B\n");
        break;
    case 0x69:
        printf("MOV\tL,C\n");
        break;
    case 0x6A:
        printf("MOV\tL,D\n");
        break;
    case 0x6B:
        printf("MOV\tL,E\n");
        break;
    case 0x6C:
        printf("MOV\tL,H\n");
        break;
    case 0x6D:
        printf("MOV\tL,L\n");
        break;
    case 0x6E:
        printf("MOV\tL,M\n");
        break;
    case 0x6F:
        printf("MOV\tL,A\n");
        break;
    case 0x70:
        printf("MOV\tM,B\n");
        break;
    case 0x71:
        printf("MOV\tM,C\n");
        break;
    case 0x72:
        printf("MOV\tM,D\n");
        break;
    case 0x73:
        printf("MOV\tM,E\n");
        break;
    case 0x74:
        printf("MOV\tM,H\n");
        break;
    case 0x75:
        printf("MOV\tM,L\n");
        break;
    case 0x76:
        printf("HLT\n");
        break;
    case 0x77:
        printf("MOV\tM,A\n");
        break;
    case 0x78:
        printf("MOV\tA,B\n");
        break;
    case 0x79:
        printf("MOV\tA,C\n");
        break;
    case 0x7A:
        printf("MOV\tA,D\n");
        break;
    case 0x7B:
        printf("MOV\tA,E\n");
        break;
    case 0x7C:
        printf("MOV\tA,H\n");
        break;
    case 0x7D:
        printf("MOV\tA,L\n");
        break;
    case 0x7E:
        printf("MOV\tA,M\n");
        break;
    case 0x7F:
        printf("MOV\tA,A\n");
        break;
    case 0x80:
        printf("ADD\tB\n");
        break;
    case 0x81:
        printf("ADD\tC\n");
        break;
    case 0x82:
        printf("ADD\tD\n");
        break;
    case 0x83:
        printf("ADD\tE\n");
        break;
    case 0x84:
        printf("ADD\tH\n");
        break;
    case 0x85:
        printf("ADD\tL\n");
        break;
    case 0x86:
        printf("ADD\tM\n");
        break;
    case 0x87:
        printf("ADD\tA\n");
        break;
    case 0x88:
        printf("ADC\tB\n");
        break;
    case 0x89:
        printf("ADC\tC\n");
        break;
    case 0x8A:
        printf("ADC\tD\n");
        break;
    case 0x8B:
        printf("ADC\tE\n");
        break;
    case 0x8C:
        printf("ADC\tH\n");
        break;
    case 0x8D:
        printf("ADC\tL\n");
        break;
    case 0x8E:
        printf("ADC\tM\n");
        break;
    case 0x8F:
        printf("ADC\tA\n");
        break;
    case 0x90:
        printf("SUB\tB\n");
        break;
    case 0x91:
        printf("SUB\tC\n");
        break;
    case 0x92:
        printf("SUB\tD\n");
        break;
    case 0x93:
        printf("SUB\tE\n");
        break;
    case 0x94:
        printf("SUB\tH\n");
        break;
    case 0x95:
        printf("SUB\tL\n");
        break;
    case 0x96:
        printf("SUB\tM\n");
        break;
    case 0x97:
        printf("SUB\tA\n");
        break;
    case 0x98:
        printf("SBB\tB\n");
        break;
    case 0x99:
        printf("SBB\tC\n");
        break;
    case 0x9A:
        printf("SBB\tD\n");
        break;
    case 0x9B:
        printf("SBB\tE\n");
        break;
    case 0x9C:
        printf("SBB\tH\n");
        break;
    case 0x9D:
        printf("SBB\tL\n");
        break;
    case 0x9E:
        printf("SBB\tM\n");
        break;
    case 0x9F:
        printf("SBB\tA\n");
        break;

    case 0xA0:
        printf("ANA\tB\n");
        break;
    case 0xA1:
        printf("ANA\tC\n");
        break;
    case 0xA2:
        printf("ANA\tD\n");
        break;
    case 0xA3:
        printf("ANA\tE\n");
        break;
    case 0xA4:
        printf("ANA\tH\n");
        break;
    case 0xA5:
        printf("ANA\tL\n");
        break;
    case 0xA6:
        printf("ANA\tM\n");
        break;
    case 0xA7:
        printf("ANA\tA\n");
        break;
    case 0xA8:
        printf("XRA\tB\n");
        break;
    case 0xA9:
        printf("XRA\tC\n");
        break;
    case 0xAA:
        printf("XRA\tD\n");
        break;
    case 0xAB:
        printf("XRA\tE\n");
        break;
    case 0xAC:
        printf("XRA\tH\n");
        break;
    case 0xAD:
        printf("XRA\tL\n");
        break;
    case 0xAE:
        printf("XRA\tM\n");
        break;
    case 0xAF:
        printf("XRA\tA\n");
        break;
    case 0xB0:
        printf("ORA\tB\n");
        break;
    case 0xB1:
        printf("ORA\tC\n");
        break;
    case 0xB2:
        printf("ORA\tD\n");
        break;
    case 0xB3:
        printf("ORA\tE\n");
        break;
    case 0xB4:
        printf("ORA\tH\n");
        break;
    case 0xB5:
        printf("ORA\tL\n");
        break;
    case 0xB6:
        printf("ORA\tM\n");
        break;
    case 0xB7:
        printf("ORA\tA\n");
        break;
    case 0xB8:
        printf("CMP\tB\n");
        break;
    case 0xB9:
        printf("CMP\tC\n");
        break;
    case 0xBA:
        printf("CMP\tD\n");
        break;
    case 0xBB:
        printf("CMP\tE\n");
        break;
    case 0xBC:
        printf("CMP\tH\n");
        break;
    case 0xBD:
        printf("CMP\tL\n");
        break;
    case 0xBE:
        printf("CMP\tM\n");
        break;
    case 0xBF:
        printf("CMP\tA\n");
        break;



















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
