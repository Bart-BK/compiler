**Compiler - Lexical**
========================

Introduction
------------------------
A [Compiler](https://en.wikipedia.org/wiki/Compiler) is computer software that transforms computer code written in one programming language (the source language) into another computer language (the target language). Compilers are a type of translator that support digital devices, primarily computers. A common reason for compilation is converting source code into a binary form known as object code to create an executable program. 


Manual
------------------------
To understand how the code works, check the [Automaton](https://github.com/Bart-BK/compiler/blob/master/Compiladores_Automato.xml) (XML)

The code need the [headers](https://github.com/Bart-BK/compiler/tree/master/headers) to work, the code uses the [table of errors](https://github.com/Bart-BK/compiler/blob/master/headers/erros.h) to show where is the lexical error, use the [table of symbols](https://github.com/Bart-BK/compiler/blob/master/headers/tabSimb.h) who show the symbols identifieds of the programming language (In this case, Portugol), and the [table of tokens](https://github.com/Bart-BK/compiler/blob/master/headers/tokens.h) who contain a list of tokens of this programming language.

To test how it works, the tests are found in:
[test-01.ptg](https://github.com/Bart-BK/compiler/blob/master/teste-01.ptg)
[test-02.ptg](https://github.com/Bart-BK/compiler/blob/master/teste-02.ptg)
[test-03.ptg](https://github.com/Bart-BK/compiler/blob/master/teste-03.ptg)

To use the compiler, use:

    ./Lexic teste-01.ptg 
  
Where the teste-01.ptg will be your code, who will be analised

Author
------------------------
Prabhát Kumar de Oliveira
