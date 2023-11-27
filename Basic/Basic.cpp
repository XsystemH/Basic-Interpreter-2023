/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <cstddef>
#include <iostream>
#include <string>
#include "evalstate.hpp"
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    EvalState state;
    Program program;
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                return 0;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);

    // void (*grammar[8]) () = {NULL, G_REM, G_LET, G_PRINT, G_INPUT, G_END, G_GOTO, G_IF};
    bool withnumber = false;
    int linenum;
    code newline;
    if (scanner.hasMoreTokens()) {
        std::string token = scanner.nextToken();
        if (scanner.TokenScanner::getTokenType(token) == NUMBER) {
            linenum = stringToInteger(token);
            
            //检查数字是否已经存在 
            //Exist: 1.后为空 line.clear
            //       2.否, 非法
            if (program.lines.find(linenum) != program.lines.end()) {
                if (!scanner.hasMoreTokens()) {
                    program.lines.erase(linenum);
                    program.functions.erase(linenum);
                }
                else {
                    //errormessage
                }
            }
            else if (!scanner.hasMoreTokens()) { // 数字不存在 但后为空
                //TODO errormessage
                return;
            }
            token = scanner.nextToken(); // 跳过行号分析后面语句的语法
        }
        // 找到对应语法进行分析(传参)
        // 部分语句需要linenumber, 否则非法
        if (token == "REM") {
            if (!withnumber) {
                //TODO error message
                return;
            }
            newline.function = REM;
            newline.rem = scanner.nextToken();
            return;
        }
        else if (token == "LET") {
            newline.function = LET;
            newline.ver1 = scanner.nextToken();
            token = scanner.nextToken(); // 读掉“=”
            newline.exp1 = parseExp(scanner);
            int val = newline.exp1->Expression::eval(state);
            state.EvalState::setValue(newline.ver1, val);
        }
        else if (token == "PRINT") {
            //
        }
        else if (token == "INPUT") {
            //
        }
        else if (token == "END") {
            if (!withnumber) {
                //TODO error message
                return;
            }
            //
        }
        else if (token == "GOTO") {
            if (!withnumber) {
                //TODO error message
                return;
            }
            //
        }
        else if (token == "IF") {
            if (!withnumber) {
                //TODO error message
                return;
            }
            //
        }
    }
}

