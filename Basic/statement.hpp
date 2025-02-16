/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface, which is an excellent model for
 * the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <string>
#include <sstream>
#include "evalstate.hpp"
#include "exp.hpp"
#include "Utils/tokenScanner.hpp"
#include "program.hpp"
#include"parser.hpp"
#include "Utils/error.hpp"
#include "Utils/strlib.hpp"

class Program;

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

    Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

    virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

    virtual void execute(EvalState &state, Program &program) = 0;

};


/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class REM : public Statement {
  
public:

    REM();
    ~REM();
    void execute(EvalState &, Program &);

};

class LET : public Statement {
    
private:

    Expression *exp = nullptr;

public:

    LET(Expression &);
    ~LET();
    void execute(EvalState &, Program &);

};

class PRINT : public Statement {

private:

    Expression *exp = nullptr;
    bool legal = true;

public:

    PRINT(EvalState &, Expression &);
    ~PRINT();
    void execute(EvalState &, Program &);

};

class INPUT : public Statement {

private:

    std::string var;

public:

    INPUT(std::string &);
    ~INPUT();
    void execute(EvalState &, Program &);

};

class END : public Statement {

public:

    END();
    ~END();
    void execute(EvalState &, Program &);

};

class GOTO : public Statement {

private:

    int linenumber;

public:

    GOTO(int &);
    ~GOTO();
    void execute(EvalState &, Program &);

};

class IF : public Statement {

private:
    
    std::string str;
    int linenumber;

public:

    IF(std::string , int &);
    ~IF();
    void execute(EvalState &, Program &);

};

#endif
