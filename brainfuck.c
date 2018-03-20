#include <stdio.h>
#include <stdlib.h>

enum instructions {
     INC_DP = '>',
     DEC_DP = '<',
     INC_BY = '+',
     DEC_BY = '-',
     OUTPUT = '.',
     INPUT  = ',',
     BEQZ   = '[',
     BNEZ   = ']'
};
    
void exec(char* src, char* ram, int sizeSrc) {
    char* ip = src;
    char* dp = ram;
    int i = 0;
    
    while(*ip != 254) {
        //~ printf("[READING]\t%c\t%ld\t%ld", *ip, ip-src, dp-ram);
        i++;
        int stack = 0;
        switch(*ip) {
            case INC_DP:
                dp++;
                break;
            case DEC_DP:
                dp--;
                break;
            case INC_BY:
                *dp = 1 + *dp;
                break;
            case DEC_BY:
                *dp = -1 + *dp;
                break;
            case OUTPUT:
                //~ printf("diocane");
                printf("%c\n", *dp);
                break;
            case INPUT:
                scanf("%c", dp);
                break;
            case BEQZ:
                if (*dp == 0) {
                    //~ printf("\t[BEQZ]");
                    for(;!(*ip == BNEZ && stack == 0); ip++) {
                        if (*ip == BNEZ)
                            stack--;
                        if (*ip == BEQZ)
                            stack++;
                    }
                }
                break;
            case BNEZ:
                if (*dp != 0) {
                    //~ printf("\t[BNEZ]");
                    
                    ip--;
                    for(; !(*ip == BEQZ && stack == 0); ip--) {
                        if (*ip == BNEZ)
                            stack++;
                        if (*ip == BEQZ)
                            stack--;
                    }
                    //~ while (1) {
                        //~ if (*ip == BEQZ && stack == 0)
                            //~ break;
                            
                        //~ if (*ip == BEQZ)
                            //~ stack--;
                        //~ if (*ip == BNEZ)
                            //~ stack++;
                        //~ ip--;
                    //~ }
                }
                break;
            default:
                printf("ISTRUZIONE NON RICONOSCIUTA");
                exit(-1);
            }
        //~ printf("\n");
        ip++;
    }
}
    
int main() {
    FILE * fileSrc = fopen("src.bf", "rb");
    if (fileSrc == NULL) {
        printf("File not found. Exiting...");
        exit(-1); 
    }
    
    fseek(fileSrc, 0L, SEEK_END);
    int sizeSrc = ftell(fileSrc);
    rewind(fileSrc);
    
    char* src = calloc(sizeSrc, sizeof(char));
    
    char ram[30000]; // = calloc(30000, sizeof(char));
    
    for(int i=0; i < sizeSrc; i++) {
        src[i] = fgetc(fileSrc);
    }
    src[sizeSrc] = 254;
    //~ for(int i=0; i<sizeSrc; i++)
        //~ printf("%c, ", src[i]);
    exec(src, ram, sizeSrc);
}
