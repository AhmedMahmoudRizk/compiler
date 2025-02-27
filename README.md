# CS321 Compiler Project
A compiler with Lexical and Parser generators implemented with C++ and tested on Java language rules.
---
## 1. Lexical Generator
Lexical Generator is the first phase in compilers, which generate a lexical automata that checks for lexical in the program according to a given rules file.
Rules file has the punctations, regular definitions and expressoins

The lexical analyzer generator is required to automatically construct a lexical analyzer from
a regular expression description of a set of tokens. The tool is required to construct a
nondeterministic finite automata (NFA) for the given regular expressions, combine these
NFAs together with a new starting state, convert the resulting NFA to a DFA, minimize it
and emit the transition table for the reduced DFA together with a lexical analyzer program
that simulates the resulting DFA machine.

**Lexical Rules:**
* The tokens of the given language are: identifiers, numbers, keywords, operators and
punctuation symbols.
* The token id matches a letter followed by zero or more letters or digits.
* The token num matches an unsigned integer or a floating- point number. The number
consists of one or more decimal digits, an optional decimal point followed by one or
more digits and an optional exponent consisting of an E followed by one or more digits.
* Keywords are reserved. The given keywords are: int, float, boolean, if, else, while.
* Operators are: +, -, *, /, =, <=, <, >, >=, !=, ==
* Punctuation symbols are parentheses, curly brackets, commas and semicolons.
* Blanks between tokens are optional.

**Lexical Rules Input File Format:**
* Lexical rules input file is a text file.
* Regular definitions are lines in the form LHS = RHS
* Regular expressions are lines in the form LHS: RHS
* Keywords are enclosed by { } in separate lines.
* Punctuations are enclosed by [ ] in separate lines
* \L represents Lambda symbol.
* The following symbols are used in regular definitions and regular expressions with the
meaning discussed in class: - | + * ( )
* Any reserved symbol needed to be used within the language, is preceded by an
escape backslash character.
---
## 2. Parser Generator
The parser generator expects an LL (1) grammar as input. It should compute First and Follow
sets and uses them to construct a predictive parsing table for the grammar.
If input file is not in LL1 form, the gernerator will do `Left Factoring` and `Left Recuresion` elimination techinques.

The table is to be used to drive a predictive top-down parser. If the input grammar is not
LL (1), an appropriate error message should be produced.
The generated parser is required to produce some representation of the leftmost derivation for
a correct input. If an error is encountered, a panic-mode error recovery routine is to be called
to print an error message and to resume parsing.
The parser generator is required to be tested using the given context free grammar of a small
subset of Java. Of course, you have to modify the grammar to allow predictive parsing.
Combine the lexical analyzer generated in phase1 and parser such that the lexical analyzer is
to be called by the parser to find the next token. Use the simple program given in phase 1 to
test the combined lexical analyzer and parser.

CFG Input File Format:
* CFG input file is a text file.
* Production rules are lines in the form LHS ::= RHS
* Production rule can be expanded over many lines.
* Terminal symbols are enclosed in single quotes.
* \L represents Lambda symbol.
* The symbol | is used in RHS of production rules with the meaning discussed in class.
* Any reserved symbol needed to be used within the language, is preceded by an escape
backslash character. 


---
## Before running:
#### Edits required:
1. Edit rules file Path with your own path in `LexicalGenerator.cpp` file in line 294 `readRulesFile` function >> 
```C++
readFile.open("/home/yousef/tests/rules.txt");
```
2. Edit input file Path with your own path in `LexicalGenerator.cpp` file in line 57 `readTestFile` function >>
```C++
readFile.open("/home/yousef/tests/input.txt");
```
3. Edit output file Path with your own path in `TestProgram.cpp` file in line 323 `executeTokensFile` function >>
```C++
outfile.open("/home/yousef/tests/tokens.txt");
```
4. Edit parser rules file Path with your own path in `InputHandler.cpp` file >> 
```C++
readFile.open("/home/yousef/tests/grammar.txt");
```
---
## Assumptions:
* Rules File should be separated by spaces between each expression and letter or word. For example, If there is a regular definition defined as 
`digit = 0-9` and a regular experssion that is `x : digityz` The lexical generator will consider `digityz` as a word not as `digit` and then `yz`
* [Maximal Munch](https://en.wikipedia.org/wiki/Maximal_munch) and Priority rule-in case of tie, first priority rule will be considerd- are appiled.
* Only `positive clousre +`, `kleene closure *`, `ORing |` and `Concatenation .` are applied, but it is very easy to add more operators in the code, just do the next:
  * edit in `LexicalAnalyzer` files >> `initOperationsMap` and `doOperationInTOS` functions
  * add the operator function in `NFAOperator`
 * Terimnals in grammar file is surronded with single quotes, ex `'mulop'`
---
## Contributers:
1. [Abo-ElHamd Ali](https://github.com/aboelhamd)
2. [Ahmed Rizk](https://github.com/AhmedMahmoudRizk)
3. [Yahia ElShahawy](https://github.com/yahia-elshahawy)


