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

    #include "ENGraph.h"

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
    #include "ENGraph.h"
    
    using namespace Gnocchi;
    
    static Parser::symbol_type yylex(Scanner &scanner, Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    
}

%lex-param {Scanner &scanner}
%lex-param {Interpreter &driver}

%parse-param {Scanner &scanner}
%parse-param {Interpreter &driver}
%parse-param {EN::Graph &graph}

%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token EOF 0;

%token <string> IDENTIFIER;

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
%token <string> STRING_LITERAL;
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

%left IDENTIFIER
%left NOTIFY_OP
%right ASSIGN ASSIGN_PLUS ASSIGN_MINUS ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_AND ASSIGN_OR ASSIGN_XOR
%left LOGIC_OR
%left LOGIC_XOR
%left LOGIC_AND
%left BINARY_OR
%left BINARY_XOR
%left BINARY_AND
%left EQ NE
%left LT LE GT GE
%left SHIFT_LEFT SHIFT_RIGHT
%left PLUS MINUS
%left MUL DIV MOD
%left HOLON_OP
%right LOGIC_NOT BINARY_NOT INC DEC
%nonassoc APOSTROPHE IS

%start program

%%

program : { driver.clear(); } statements

statements : statement statements 
           | %empty

statement : definition
          | "edge" create_edge ";"
          | expr ";"
            
definition : vertex_definition

vertex_definition : definition_header "vertex" vertex_type notification_params state_expr interfaces vertex_body

definition_header : visibility | visibility name "is"

name : IDENTIFIER | "head"

visibility : "public" | "private" | %empty

vertex_type : primitive_type | %empty

notification_params : %empty | "(" notification_param param_list ")"

param_list : "," notification_param param_list | %empty

notification_param : IDENTIFIER "is" primitive_type |
                     IDENTIFIER "is" primitive_type "default" expr

state_expr : %empty | expr | "bound" expr

interfaces : %empty | IDENTIFIER | IDENTIFIER "," interfaces

vertex_body : "," vertex_body_part vertex_body | %empty

vertex_body_part : default_notify | create_edge | enabled_ops | initial_value

default_notify : "this" "->" "default" edge_function

enabled_ops : "enables" operations | "disables" operations

operations : operation operations | %empty

operation : "read" | "notify" | "listen"

initial_value : "initialise" expr

create_edge : access "->" vertex_list edge_function
            |  vertex_list "->"  access edge_function

vertex_list : access _vertex_list

_vertex_list : %empty | "," access _vertex_list

edge_function : when_clause with_clause

when_clause : %empty | "when" expr
with_clause : %empty | "with" expr 

primitive_type : scalar_primitive_type | primitive_type "[" expr "]"

scalar_primitive_type : "int8" | "int16" | "int24" | "int32" | "int" | "uint8"
                      | "uint16" | "uint24" | "uint32" | "uint" | "float"
                      | "double" | "number" | "bool" | "char"

expr : notify | binary_expr

binary_expr : unary_left binary_op unary_left

binary_op : IDENTIFIER | ":=" | "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "^="  
            | "||" | "^^" | "&&" | "|"  | "^"  | "&"  | "==" | "!=" | "<" | "<="
            | ">" | ">=" | "<<" | ">>" | "+"  | "-" | "*"  | "/"  | "%" | "<>"


unary_left : unary_right
            | "<>" unary_left
            | unary_left_op unary_left

unary_left_op : "-" | "!" | "~" | "++" | "--"

unary_right : access 
            | "<>" unary_right
            | unary_right_operator unary_right

unary_right_operator : "++" | "--"

access : primary_expr
       | access "(" ")" access
       | access "(" param_list ")" access 
       | access "[" expr "]" access

param_list :  expr _param_list
_param_list : %empty | "," expr _param_list

primary_expr : notify 
             | SIGNED_INTEGER_LITERAL
             | UNSIGNED_INTEGER_LITERAL
             | BOOL_LITERAL
             | CHAR_LITERAL
             | STRING_LITERAL
             | DOUBLE_LITERAL
             | FLOAT_LITERAL
             | name
             | "this" "'"
             | "this"
             | "(" expr ")" 

notify :  "->" access
         | param_list "->" access


%%

// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc , const string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << @$ << " " << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << loc << endl;
}
