//
// Created by yousef on 13/04/18.
//

#ifndef CLEAN_COMPILER_NFAOPERATOR_H
#define CLEAN_COMPILER_NFAOPERATOR_H
#include "NFA.h"

NFA OR(NFA nfa1, NFA nfa2);
NFA AND(NFA nfa1, NFA nfa2);
NFA kleeneClosure(NFA nfa);
NFA positiveClosure(NFA nfa);


#endif //CLEAN_COMPILER_NFAOPERATOR_H
