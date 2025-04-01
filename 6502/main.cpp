#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

struct CPU{
    

    Word PC;        // Program Counter
    Word SP;        // Stack Pointer

    Byte A, X, Y;   // Registers
    
};


int main(){

    return 0;
}