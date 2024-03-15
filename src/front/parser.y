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

%token DECLARE "declare";
%token DELETE "delete";
%token IF "if";
%token WHILE "while";

/* Literals */
%token <int> INTEGER;

%token SEMICOLON ";";

%token LEFTPAR "(";
%token RIGHTPAR ")";
%token LSBRACKET "[";
%token RSBRACKET "]";
%token LCBRACKET "{";
%token RCBRACKET "}";


%left LT GT EQ NE LE GE
%right LEFTPAR LSBRACKET LCBRACKET ASSIGN 
%left PLUS MINUS RIGHTPAR RSBRACKET RCBRACKET

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
                  | "declare" IDENTIFIER "[" INTEGER "]" ";"{
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
            | INTEGER {
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
