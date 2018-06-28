./compiler/proper_compiler < $1 > proper_compiled.c
@gcc proper_compiled.c run/var/*.c -o proper.out > /dev/null 2>&1
if [ $? -ne 0 ]
then
    echo "Compile failed!"
    exit 1
fi