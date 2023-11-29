/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"
#include "Utils/error.hpp"
#include "evalstate.hpp"
#include "exp.hpp"
#include <iostream>
#include <string>


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

REM::REM() = default;
REM::~REM() = default;
void REM::execute(EvalState &state, Program &program) {
  return;
}

LET::LET(Expression &exp) {
    this->exp = &exp;
}
LET::~LET() {
    delete exp;
}
void LET::execute(EvalState &state, Program &program) {
    exp->eval(state);
}

PRINT::PRINT(EvalState &state, Expression &exp) {
    try {
        this->val = new int(exp.eval(state));
    }catch (ErrorException &ex) {
        std::cout << ex.getMessage() << "\n";
        legal = false;
        delete val;
    }
}
PRINT::~PRINT() {
    // int 要删吗？
    delete val;
}
void PRINT::execute(EvalState &state, Program &program) {
    if (legal) std::cout << *val << "\n";
}

INPUT::INPUT(std::string &v) {
  this->var = v;
}
INPUT::~INPUT() = default;
void INPUT::execute(EvalState &state, Program &program) {
    std::string temp;
    while (1) {
        try {
            std::cout << " ? ";
            getline(std::cin, temp);
            // std::cout << temp << "\n";
            int val = stringToInteger(temp);
            state.setValue(var, val);
        } catch(ErrorException &ex) {
            std::cout << "INVALID NUMBER\n";
            continue;
        }
        break;
    }
}

END::END() = default;
END::~END() = default;
void END::execute(EvalState &state, Program &program) {
    program.linejump = -1;
}

GOTO::GOTO(int &num) {
    linenumber = num;
}
GOTO::~GOTO() = default;
void GOTO::execute(EvalState &state, Program &program) {
    program.linejump = linenumber;
}

IF::IF(Expression *e, int &n) {
    this->exp = e;
    this->linenumber = n;
}
IF::~IF() {
    delete exp;
}
void IF::execute(EvalState &state, Program &program) {
    return;
}