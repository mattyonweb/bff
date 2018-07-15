/* BRAINFUCK INTERPRETER
 * Lanciato da linea di comando:
 * ./brainfuck nomefile.bf <debug {0|1}>
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#define RAMSIZE 30000
#define NEWLINE 0

void exec(char* src, int debug, int newline);

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
    
int main(int argv, char** argc) {
    int debug;
    
    if (argv == 1 || argv > 3) {
        printf("There should be only 2/3 args. Exiting...\n");
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
    rewind(fileSrc); 

    char* src = calloc(size, sizeof(char));

    int i = 0;
    char c;
    while ((c = fgetc(fileSrc)) != EOF) {
        if (c == '>' || c == '<' ||c == '.' ||c == ',' ||c == '-' ||c == '+' ||c == '[' ||c == ']')
            src[i++] = c;
    }
    src[++i] = -1;
    
    exec(src, debug, NEWLINE);
}


void exec(char* src, int debug, int newline) {
    char ram[RAMSIZE] = {0};
    char* dp = ram;
    char* ip = src;
    
    while(*ip != -1) {
        int stack = 0;
        int innerStackLvl;

        if (dp - ram >= RAMSIZE) {
            printf("Out of bound error\n");
            exit(-1);
        }
        
        if (debug) 
            printf("[READING]\t%c\t%d\t%d\t%d", *ip, ip-src, dp-ram, *dp);
        
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
                printf("%c", *dp);
                if (newline) printf("\n");
                break;
            case INPUT:
                scanf(" %c", dp);
                break;
            case BEQZ:
                if (*dp == 0) {
                    if (debug) printf("\t[BEQZ]");
                    
                    ip++;
                    innerStackLvl = 0;
                    
                    for(;!(*ip == BNEZ && innerStackLvl == 0); ip++) {
                        if (*ip == BNEZ)    // Sono necessarie queste righe?
                            innerStackLvl--;        // Tutte le [ e ] all'interno di un
                        if (*ip == BEQZ)    // blocco [] sono da ignorare no?
                            innerStackLvl++;
                    }
                }
                else {
                    stack++;
                }
                break;
            case BNEZ:
                if (*dp != 0) {
                    ip--;

                    innerStackLvl = 0;
                    for(; !(*ip == BEQZ && innerStackLvl == 0); ip--) {
                        if (*ip == BNEZ)
                            innerStackLvl++;
                        if (*ip == BEQZ)
                            innerStackLvl--;
                    }
                } else {
                    stack--;
                }
                break;
            }
        if (debug) printf("\n");
        ip++;
    }
}
