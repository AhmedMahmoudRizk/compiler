cmake_minimum_required(VERSION 3.8)
project(clean_compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Lexical/NFA.cpp Lexical/NFA.h Lexical/DFA.cpp Lexical/DFA.h Lexical/Graph.cpp Lexical/Graph.h Lexical/RulesParser.cpp Lexical/RulesParser.h Lexical/LexicalAnalyzer.cpp Lexical/LexicalAnalyzer.h Lexical/GroupedNFA.cpp Lexical/GroupedNFA.h Lexical/NFAOperator.cpp Lexical/NFAOperator.h Lexical/Bimap.h Lexical/NFAToDFA.cpp Lexical/NFAToDFA.h Lexical/TestProgram.cpp Lexical/TestProgram.h Parser/Symbol.cpp Parser/Symbol.h  Parser/ParserGenerator.cpp Parser/ParserGenerator.h Parser/ParsingTable.cpp Parser/ParsingTable.h Parser/ParserTracer.cpp Parser/ParserTracer.h Parser/Symbol.cpp Parser/Symbol.h Parser/Terminal.cpp Parser/Terminal.h Parser/NonTerminal.cpp Parser/NonTerminal.h  Parser/ToLL1Converter.cpp Parser/ToLL1Converter.h Parser/ToLL1Converter.cpp Parser/ToLL1Converter.h Parser/InputHandler.cpp Parser/InputHandler.h)
add_executable(clean_compiler ${SOURCE_FILES})