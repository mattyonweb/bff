# bff - Brainfuck interpreter

A simple but strict brainfuck interpreter written in C. 

Some notes:
- The interpreter has a default memory size of 30.000 cells.
- Every cell has dimension of `sizeof(char)`, usually 1 byte; every value stored has to be considered modulo maxValue, usually 255.
- There is no `#` or `!` instruction.


### Installation
    git clone https://github.com/mattyonweb/bff.git
    cd bff
    make

To run the tests present in the folder `tests`, type:

	make test
