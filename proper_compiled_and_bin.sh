./compiler/proper_compiler < $1 > proper_compiled.c 2> debuggingGccErrors.txt
gcc proper_compiled.c run/var/*.c -o proper.out > debuggingGccErrors.txt 2>&1
if [ $? -ne 0 ]
then
    echo "Dear Programmer, you are not proper enough: compile failed."
    exit 1
else
    echo "CheeriO"
    exit 0
fi

