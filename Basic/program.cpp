/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"
#include "Utils/strlib.hpp"
#include "evalstate.hpp"
#include "exp.hpp"
#include "parser.hpp"
#include "statement.hpp"
#include <cstddef>
#include <string>
#include <utility>

Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    List.clear();
    Func.clear();
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    // They have line numbers: REM LET PRINT INPUT END GOTO IF
    if (List.count(lineNumber) != 0) {
        // repalce
        List.erase(lineNumber);
    }
    List.insert(std::make_pair(lineNumber, line));
    // Statement addfunc(line); ???
}

void Program::removeSourceLine(int lineNumber) {
    List.erase(lineNumber);
    Func.erase(lineNumber);
}

std::string Program::getSourceLine(int lineNumber) {
    if (List.count(lineNumber) == 0) {
        return std::string("");
    }
    return List[lineNumber];
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if (Func.count(lineNumber)) {
        Func.erase(lineNumber);
    }
    Func[lineNumber] = stmt;
}

// void Program::removeSourseLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
//    Statement *s;
//    setParsedStatement(lineNumber, s);
//    return s;
    if (List.count(lineNumber) == 0) {
        return NULL;
    }
    return Func[lineNumber];
}

int Program::getFirstLineNumber() {
    if (List.empty()) {
        return -1;
    }
    return List.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
    if (linejump != -2) {
        int temp = linejump;
        linejump = -2;
        return temp;
    }
    auto it = List.find(lineNumber);
    if (it != List.end()) {
        it++;
        if (it != List.end()) return it->first;
        else return -1;
    }
    return -1;
}

Statement *Program::ParseStatement(EvalState &state, TokenScanner &scanner) {
    // REM LET PRINT INPUT END GOTO IF
    std::string token = scanner.nextToken();
    if (token == "REM") {
        return new REM();
    }
    else if (token == "LET") {
        Expression *exp = parseExp(scanner);
        return new LET(*exp);
    }
    else if (token == "PRINT") {
        Expression *exp = parseExp(scanner);
        return new PRINT(state, *exp);
    }
    else if (token == "INPUT") {
        token = scanner.nextToken();
        return new INPUT(token);
    }
    else if (token == "END") {
        return new END();
    }
    else if (token == "GOTO") {
        token = scanner.nextToken();
        int gt = stringToInteger(token);
        return new GOTO(gt);
    }
    return NULL;
}


