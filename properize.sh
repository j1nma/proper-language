cd compiler
if [ $1 = "-debug" ]
then
	make debug
	cd ..
	./proper_compiled_and_bin.sh $2
else
	make all
	cd ..
	./proper_compiled_and_bin.sh $1
	rm debuggingGccErrors.txt
fi
rm proper_compiled.c
