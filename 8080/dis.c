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


//reading the data inside file into memory buffer(named data)
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
        printf("LXI\tB,#$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
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
        printf("MVI\tB\t#$%02x\n",currentOpcode[1]);
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
    case 0x0A:
        printf("LDAX\tB\n");
        break;
    case 0x0B:
        printf("DCX\tB\n");
        break;
    case 0x0C:
        printf("INR\tC\n");
        break;
    case 0x0D:
        printf("DCR\tC\n");
        break;
    case 0x0E:
        printf("MVI\tC#$%02x",currentOpcode[0]);
        break;
    case 0x0F:
        printf("RRC\tC\n");
        break;

    case 0x10:
        printf("NOP\n");
        break;
    case 0x11:
        printf("LXI\tD\t#$%02x%02x", currentOpcode[2],currentOpcode[1]);
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
        printf("MVI\tD\t#0x%02x\n",currentOpcode[1]);
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
        printf("MVI\tE\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0x1F:
        printf("RAR\n");
        break;


    case 0x20:
        printf("NOP\n");
        break;
    case 0x21:
        printf("LXI\tH\t#%02x%02x\n", currentOpcode[2], currentOpcode[1]);
        opbytes=3;
        break;
    case 0x22:
        printf("SHLD\t$%02x%02x\n", currentOpcode[2], currentOpcode[1]); //check the formatting of SHLD
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
        printf("MVI\tH\t#$%02x\n",currentOpcode[1]);
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
        printf("LHLD\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
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
        printf("MVI\tL\t#$%02x\n",currentOpcode[0]);
        opbytes = 2;
        break;
    case 0x2F:
        printf("CMA\t\n");
        break;

    case 0x30:
        printf("NOP\n");
        break;
    case 0x31:
        printf("LXI\tSP\t#$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0x32:
        printf("STA\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
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
        printf("MVI\tM\t#$%02x\n",currentOpcode[1]);
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
        printf("LDA\t%$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
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
        printf("MVI\tA\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
    case 0x3F:
        printf("CMC\n");
        break;
    case 0x40:
        printf("MOV\tB\tB\n");
        break;
    case 0x41:
        printf("MOV\tB\tC\n");
        break;
    case 0x42:
        printf("MOV\tB\tD\n");
        break;
    case 0x43:
        printf("MOV\tB\tE\n");
        break;
    case 0x44:
        printf("MOV\tB\tH\n");
        break;
    case 0x45:
        printf("MOV\tB\tL\n");
        break;
    case 0x46:
        printf("MOV\tB\tM\n");
        break;
    case 0x47:
        printf("MOV\tB\tA\n");
        break;
    case 0x48:
        printf("MOV\tC\tB\n");
        break;
    case 0x49:
        printf("MOV\tC\tC\n");
        break;
    case 0x4a:
        printf("MOV\tC\tD\n");
        break;
    case 0x4B:
        printf("MOV\tC\tE\n");
        break;
    case 0x4C:
        printf("MOV\tC\tH\n");
        break;
    case 0x4D:
        printf("MOV\tC\tL\n");
        break;
    case 0x4E:
        printf("MOV\tC\tM\n");
        break;
    case 0x4F:
        printf("MOV\tC\tA\n");
        break;
    case 0x50:
        printf("MOV\tD\tB\n");
        break;
    case 0x51:
        printf("MOV\tD\tC\n");
        break;
    case 0x52:
        printf("MOV\tD\tD\n");
        break;
    case 0x53:
        printf("MOV\tD\tE\n");
        break;
    case 0x54:
        printf("MOV\tD\tH\n");
        break;
    case 0x55:
        printf("MOV\tD\tL\n");
        break;
    case 0x56:
        printf("MOV\tD\tM\n");
        break;
    case 0x57:
        printf("MOV\tD\tA\n");
        break;
    case 0x58:
        printf("MOV\tE\tB\n");
        break;
    case 0x59:
        printf("MOV\tE\tC\n");
        break;
    case 0x5A:
        printf("MOV\tE\tD\n");
        break;
    case 0x5B:
        printf("MOV\tE\tE\n");
        break;
    case 0x5C:
        printf("MOV\tE\tH\n");
        break;
    case 0x5D:
        printf("MOV\tE\tL\n");
        break;
    case 0x5E:
        printf("MOV\tE\tM\n");
        break;
    case 0x5F:
        printf("MOV\tE\tA\n");
        break;
    case 0x60:
        printf("MOV\tH\tB\n");
        break;
    case 0x61:
        printf("MOV\tH\tC\n");
        break;
    case 0x62:
        printf("MOV\tH\tD\n");
        break;
    case 0x63:
        printf("MOV\tH\tE\n");
        break;
    case 0x64:
        printf("MOV\tH\tH\n");
        break;
    case 0x65:
        printf("MOV\tH\tL\n");
        break;
    case 0x66:
        printf("MOV\tH\tM\n");
        break;
    case 0x67:
        printf("MOV\tH\tA\n");
        break;
    case 0x68:
        printf("MOV\tL\tB\n");
        break;
    case 0x69:
        printf("MOV\tL\tC\n");
        break;
    case 0x6A:
        printf("MOV\tL\tD\n");
        break;
    case 0x6B:
        printf("MOV\tL\tE\n");
        break;
    case 0x6C:
        printf("MOV\tL\tH\n");
        break;
    case 0x6D:
        printf("MOV\tL\tL\n");
        break;
    case 0x6E:
        printf("MOV\tL\tM\n");
        break;
    case 0x6F:
        printf("MOV\tL\tA\n");
        break;
    case 0x70:
        printf("MOV\tM\tB\n");
        break;
    case 0x71:
        printf("MOV\tM\tC\n");
        break;
    case 0x72:
        printf("MOV\tM\tD\n");
        break;
    case 0x73:
        printf("MOV\tM\tE\n");
        break;
    case 0x74:
        printf("MOV\tM\tH\n");
        break;
    case 0x75:
        printf("MOV\tM\tL\n");
        break;
    case 0x76:
        printf("HLT\n");
        break;
    case 0x77:
        printf("MOV\tM\tA\n");
        break;
    case 0x78:
        printf("MOV\tA\tB\n");
        break;
    case 0x79:
        printf("MOV\tA\tC\n");
        break;
    case 0x7A:
        printf("MOV\tA\tD\n");
        break;
    case 0x7B:
        printf("MOV\tA\tE\n");
        break;
    case 0x7C:
        printf("MOV\tA\tH\n");
        break;
    case 0x7D:
        printf("MOV\tA\tL\n");
        break;
    case 0x7E:
        printf("MOV\tA\tM\n");
        break;
    case 0x7F:
        printf("MOV\tA\tA\n");
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
    case 0xC0:
        printf("RNZ\n");
        break;
    case 0xC1:
        printf("POP\tB\n");
        break;
    case 0xC2:
        printf("JNZ\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xC3:
        printf("JMP\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xC4:
        printf("CNZ\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xC5:
        printf("PUSH\tB\n");
        break;
    case 0xC6:
        printf("ADI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xC7:
        printf("RST\t0\n");
        break;
    case 0xC8:
        printf("RZ\n");
        break;
    case 0xC9:
        printf("RET\n");
        break;
    case 0xCA:
        printf("JZ\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xCB:
        printf("JMP\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xCC:
        printf("CZ\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xCD:
        printf("CALL\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xCE:
        printf("ACI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xCF:
        printf("RST\t1\n");
        break;


    case 0xD0:
        printf("RNC\n");
        break;
    case 0xD1:
        printf("POP\tD\n");
        break;
    case 0xD2:
        printf("JNC\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xD3:
        printf("OUT\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xD4:
        printf("CNC\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xD5:
        printf("PUSH\tD\n");
        break;
    case 0xD6:
        printf("SUI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xD7:
        printf("RST\t2\n");
        break;
    case 0xD8:
        printf("RC\n");
        break;
    case 0xD9:
        printf("RET\n");
        break;
    case 0xDA:
        printf("JC\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xDB:
        printf("IN\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xDC:
        printf("CC\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xDD:
        printf("CALL\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xDE:
        printf("SBI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xDF:
        printf("RST\t3\n");
        break;
    case 0xE0:
        printf("RPO\n");
        break;
    case 0xE1:
        printf("POP\tH\n");
        break;
    case 0xE2:
        printf("JPO\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xE3:
        printf("XTHL\n");
        break;
    case 0xE4:
        printf("CPO\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xE5:
        printf("PUSH\tH\n");
        break;
    case 0xE6:
        printf("ANI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xE7:
        printf("RST\t4\n");
        break;
    case 0xE8:
        printf("RPE\n");
        break;
    case 0xE9:
        printf("PCHL\n");
        break;
    case 0xEA:
        printf("JPE\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xEB:
        printf("XCHG\n");
        break;
    case 0xEC:
        printf("CPE\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xED:
        printf("CALL\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xEE:
        printf("XRI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xEF:
        printf("RST\t5\n");
        break;
    case 0xF0:
        printf("RP\n");
        break;
    case 0xF1:
        printf("POP\tPSW\n");
        break;
    case 0xF2:
        printf("JP\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xF3:
        printf("DI");
        break;
    case 0xF4:
        printf("CP\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xF5:
        printf("PUSH\tPSW\n");
        break;
    case 0xF6:
        printf("ORI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xF7:
        printf("RST\t6\n");
        break;
    case 0xF8:
        printf("RM\n");
        break;
    case 0xF9:
        printf("SPHL\n");
        break;
    case 0xFA:
        printf("JM\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xFB:
        printf("EI\n");
        break;
    case 0xFC:
        printf("CM\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xFD:
        printf("CALL\t$%02x%02x\n",currentOpcode[2],currentOpcode[1]);
        opbytes = 3;
        break;
    case 0xFE:
        printf("CPI\t#$%02x\n",currentOpcode[1]);
        opbytes = 2;
        break;
    case 0xFF:
        printf("RST\t7\n");
        break;

    default:
        printf("UNKNOWN Instructions: 0x%02x\n",*currentOpcode);
        break;
    }
    return opbytes;

}
