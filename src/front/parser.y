%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.7.4"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { Gnocchi }

%code requires
{
    #include <iostream>
    #include <string>
    #include <sstream>
    #include <memory>
    #include <fstream>

    using namespace std;

    namespace Gnocchi {
        class Scanner;
        class Interpreter;
    }

}

%code top
{
    #include <iostream>
    #include <fstream>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    using namespace Gnocchi;
    
    static Parser::symbol_type yylex(Scanner &scanner, Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    
}

%lex-param {Scanner &scanner}
%lex-param {Interpreter &driver}

%parse-param {Scanner &scanner}
%parse-param {Interpreter &driver}

%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token EOF 0;

%token <std::string> IDENTIFIER;

/* keywords */
%token EDGE "edge";
%token ATOM "atom";
%token THIS "this";
%token HEAD "head";
%token PUBLIC "public";
%token PRIVATE "private";
%token IS "is";
%token VERTEX "vertex";
%token BOUND "bound";
%token DEFAULT "default";
%token WHEN "when";
%token WITH "with";

%token ENABLES "enables";
%token DISABLES "disables";

%token READ "read";
%token LISTEN "listen";
%token NOTIFY "notify";

%token INITIALISE "initialise"

%token HOLON "holon"

/* type names */

%token INT "int";
%token INT8 "int8";
%token INT16 "int16";
%token INT24 "int24";
%token INT32 "int32";

%token UINT "uint";
%token UINT8 "uint8";
%token UINT16 "uint16";
%token UINT24 "uint24";
%token UINT32 "uint32";

%token FLOAT "float";
%token DOUBLE "double";
%token NUMBER "number";
%token BOOL "bool";
%token CHAR "char";

%token REF "ref";
%token TO "to";
%token TYPE "type";

%token SAME "same";

%token AS "as";

/* Literals */
%token <long long> SIGNED_INTEGER_LITERAL;
%token <unsigned long long> UNSIGNED_INTEGER_LITERAL;
%token <bool> BOOL_LITERAL;
%token <char> CHAR_LITERAL;
%token <std::string> STRING_LITERAL;
%token <double> DOUBLE_LITERAL;
%token <float> FLOAT_LITERAL;

/* punctuation */
%token SEMICOLON ";";
%token COMMA ",";
%token COLON ":";

%token LPAR "(";
%token RPAR ")";
%token LSBRACKET "[";
%token RSBRACKET "]";
%token LCBRACKET "{";
%token RCBRACKET "}";

/* operators */
%token NOTIFY_OP "->"
%token ELLIPSIS "..."
%token HOLON_OP "<>"

%token ASSIGN ":=";
%token ASSIGN_PLUS "+=";
%token ASSIGN_MINUS "-=";
%token ASSIGN_MUL "*=";
%token ASSIGN_DIV "/=";
%token ASSIGN_MOD "%=";
%token ASSIGN_AND "&=";
%token ASSIGN_OR "|=";
%token ASSIGN_XOR "^=";
%token LOGIC_OR "||";
%token LOGIC_XOR "^^";
%token LOGIC_AND "&&";
%token BINARY_OR "|";
%token BINARY_XOR "^";
%token BINARY_AND "&";
%token EQ "==";
%token NE "!=";
%token LT "<";
%token LE "<=";
%token GT ">";
%token GE ">=";
%token SHIFT_LEFT "<<";
%token SHIFT_RIGHT ">>";
%token PLUS "+";
%token MINUS "-";
%token MUL "*";
%token DIV "/";
%token MOD "%";
%token LOGIC_NOT "!";
%token BINARY_NOT "~";
%token INC "++";
%token DEC "--";
%token DOT .;
%token APOSTROPHE "'";

%left LT GT EQ NE LE GE
%right LPAR LSBRACKET LCBRACKET ASSIGN 
%left PLUS MINUS RPAR RSBRACKET RCBRACKET

%start program

%%

program : %empty {   
            driver.clear();
        }
        | program statement {
        }
        ;

statement : if_statement 
          | while_statement
          | declare_statement
          | delete_statement
          | assign_statement;
            
if_statement : "if" "(" expression  ")" "{" statements "}" {
                };

while_statement : "while" "(" expression ")" "{" statements "}" {
                };

declare_statement : "declare" IDENTIFIER ";" {
                  }
                  | "declare" IDENTIFIER "=" expression ";" {
                  }
                  | "declare" IDENTIFIER "[" UNSIGNED_INTEGER_LITERAL "]" ";"{
                  };

delete_statement : "delete" IDENTIFIER ";"{
                  };

assign_statement : IDENTIFIER "=" expression ";" {
                  }
                 | IDENTIFIER "[" expression "]" "=" expression ";" {
                  };

statements : statement {
            }
           | statement statements {
           };

expression : IDENTIFIER {
            } 
            | IDENTIFIER "[" expression "]" {
            }
            | UNSIGNED_INTEGER_LITERAL {
            }
            | expression "+" expression {
            }
            | expression "-" expression {
            }
            | expression "==" expression {
            }
            | expression  "!="  expression {
            }
            | expression ">" expression {
            }
            | expression ">=" expression {
            }
            | expression "<" expression {
            }
            | expression "<=" expression {
            }
            ;

%%

// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << @$ << " " << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << loc << endl;
}
