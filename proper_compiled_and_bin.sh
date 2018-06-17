./compiler/proper_compiler < $1 > proper_compiled.c
gcc proper_compiled.c runtime/*.c -o proper.out