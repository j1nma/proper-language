# Proper Language

A language for the ones with style and good taste.

Automata, Language Theory and Compilers. 
I.T.B.A.
1Q-2018
Group ALT

---

## Scripts

```
./properize.sh your_proper_program.proper
```

Or if prefered, with proper_compiler already compiled at *compiler* directory, generate proper compiled and executable:

```
./proper_compiled_and_bin.sh your_proper_program.proper
```


## Compiling compiler

Obtain *proper_compiler* inside *compiler* directory:


```
make all
```

Clean files with:


```
make clean
```

Debug files with:


```
make debug
```

## Compiling your program


```
./compiler/proper_compiler < your_proper_program.proper > your_compiled_proper.c
```

Obtain executable from *your_compiled_proper.c* with:
```
gcc compiled.c runtime/*.c -o proper.out
```


## Running

```
./proper.out
```
