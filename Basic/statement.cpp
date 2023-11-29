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
    // try {
    //     this->val = new int(exp.eval(state));
    // }catch (ErrorException &ex) {
    //     std::cout << ex.getMessage() << "\n";
    //     legal = false;
    //     delete val;
    // }
    this->exp = &exp;
}
PRINT::~PRINT() {
    // int 要删吗？
    delete exp;
}
void PRINT::execute(EvalState &state, Program &program) {
    legal = true;
    int val;
    try {
        val = int(exp->eval(state));
    }catch (ErrorException &ex) {
        std::cout << ex.getMessage() << "\n";
        legal = false;
    }
    if (legal) std::cout << val << "\n";
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
    if (program.LineNumberIsLegal(linenumber))
        program.linejump = linenumber;
    else {
        std::cout << "LINE NUMBER ERROR\n";
    }
}

IF::IF(std::string str, int &n) {
    this->str = str;
    this->linenumber = n;
    // std::cout << "Store OK with: " << exp->toString() << std::endl;
}
IF::~IF() = default;
void IF::execute(EvalState &state, Program &program) {
    bool flag = false;
    char op = '=';
    int i = 0;
    for(; i < str.size(); i++) {
        if (str[i] == '<') {
            op = '<';
            str[i] = '=';
            break;
        }
        if (str[i] == '>') {
            op = '>';
            str[i] = '=';
            break;
        }
    }
    TokenScanner rawexp;
    rawexp.ignoreWhitespace();
    rawexp.scanNumbers();
    rawexp.setInput(str);
    Expression *exp = parseExp(rawexp);
    // std::cout << "OP Get!" << std::endl;
    Expression *lhs = ((CompoundExp *) exp)->getLHS();
    Expression *rhs = ((CompoundExp *) exp)->getRHS();
    // std::cout << "l&r Get!" << std::endl;
    int lval = int(lhs->eval(state));
    int rval = int(rhs->eval(state));
    // std::cout << "Value Get!" << std::endl;
    if (op == '=' && lval == rval) flag = true;
    if (op == '>' && lval > rval) flag = true;
    if (op == '<' && lval < rval) flag = true;
    // if (op == ">=" && lval >= rval) flag = true; NO THIS OPERATOR
    // if (op == "<=" && lval <= rval) flag = true;

    if (flag) {
        if (program.LineNumberIsLegal(linenumber))
            program.linejump = linenumber;
        else {
            std::cout << "LINE NUMBER ERROR\n";
        }
    }
    if (i < str.size()) str[i] = op;
    delete exp;
    // delete lhs;
    // delete rhs;
    return;
}