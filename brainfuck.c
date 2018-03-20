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
    
void exec(char* src, int debug) {
    char ram[30000];
    char* dp = ram;
    char* ip = src;
    
    while(*ip != 10) { //0x0a
        int stack = 0;
        if (debug) 
            printf("[READING]\t%c\t%ld\t%ld\t%d", *ip, ip-src, dp-ram, *dp);
        
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
                printf("%c\n", *dp);
                break;
            case INPUT:
                scanf("%c", dp);
                break;
            case BEQZ:
                if (*dp == 0) {
                    if (debug) printf("\t[BEQZ]");
                    
                    ip++;
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
                    if (debug) printf("\t[BNEZ]");
                    
                    ip--;
                    for(; !(*ip == BEQZ && stack == 0); ip--) {
                        if (*ip == BNEZ)
                            stack++;
                        if (*ip == BEQZ)
                            stack--;
                    }
                }
                break;
            }
        if (debug) printf("\n");
        ip++;
    }
}
    
int main(int argv, char** argc) {
    int debug;
    
    if (argv == 1 || argv > 3) {
        printf("There should be only 2/3 args. Exiting...");
        exit(-1);
    }
    if (argv == 2)
        debug = 0;
    else
        debug = atoi(argc[2]);
    
    FILE * fileSrc = fopen(argc[1], "rb");
    if (fileSrc == NULL) {
        printf("File not found. Exiting...");
        exit(-1); 
    }
    
    //lunghezza del file (che palle)
    fseek(fileSrc, 0L, SEEK_END);
    int size = ftell(fileSrc);    
    char* src = calloc(size, sizeof(char));
    
    rewind(fileSrc);    //riporta il pointer di fileSrc a inizio file
    char c;
    for(int i=0; (c = fgetc(fileSrc)) != 10; i++) {
        src[i] = c;
    }
    src[size] = 10;
    
    exec(src, debug);
}
