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
    if (List.count(lineNumber) == 0) {
        throw error;
        return;
    }
    if (Func.count(lineNumber)) {
        Func.erase(lineNumber);
    }
    Func[lineNumber] = stmt;
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
//    Statement *s;
//    setParsedStatement(lineNumber, s);
//    return s;
    if (Func.count(lineNumber) == 0) {
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
    auto it = List.find(lineNumber);
    if (it != List.end()) {
        it++;
        if (it != List.end()) return it->first;
        else return -1;
    }
    return -1;
}

//more func to add
//todo


