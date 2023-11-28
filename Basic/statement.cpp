/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"
#include "evalstate.hpp"
#include "exp.hpp"
#include <string>


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

REM::REM(std::string &s) {
  this->note = &s;
}
REM::~REM() {
  delete note;
}
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
    this->val = exp.eval(state);
}
PRINT::~PRINT() {
    // int 要删吗？
}
void PRINT::execute(EvalState &state, Program &program) {
    std::cout << val << "\n";
}