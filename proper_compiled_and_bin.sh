./compiler/proper_compiler < $1 > proper_compiled.c
gcc proper_compiled.c run/var/*.c -o proper.out > debuggingGccErrors.txt 2>&1