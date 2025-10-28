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
    #include "BinaryExpr.h"
    #include "LiteralExpr.h"
    #include "NotifyExpr.h"
    #include "UnaryExpr.h"
    #include "VertexAccessExpr.h"
    #include "ENOperators.h"

    using namespace std;

    namespace Gnocchi {
        class Scanner;
        class Interpreter;
    }

}

%code top
{
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
%token <EN::Visibility> PUBLIC "public";
%token <EN::Visibility> PRIVATE "private";
%token <EN::Visibility> DECLARE "declare";
%token IS "is";
%token VERTEX "vertex";
%token STATE "state";
%token BOUND "bound";
%token DEFAULT "default";
%token WHEN "when";
%token WITH "with";

%token ENABLES "enables";
%token DISABLES "disables";

%token <EN::AllowedOperations> READ "read";
%token <EN::AllowedOperations> LISTEN "listen";
%token <EN::AllowedOperations> NOTIFY "notify";

%token INITIALISE "initialise"

%token HOLON "holon"

/* type names */

%token <std::weak_ptr<EN::Type>> INT "int";
%token <std::weak_ptr<EN::Type>> INT8 "int8";
%token <std::weak_ptr<EN::Type>> INT16 "int16";
%token <std::weak_ptr<EN::Type>> INT24 "int24";
%token <std::weak_ptr<EN::Type>> INT32 "int32";

%token <std::weak_ptr<EN::Type>> UINT "uint";
%token <std::weak_ptr<EN::Type>> UINT8 "uint8";
%token <std::weak_ptr<EN::Type>> UINT16 "uint16";
%token <std::weak_ptr<EN::Type>> UINT24 "uint24";
%token <std::weak_ptr<EN::Type>> UINT32 "uint32";

%token <std::weak_ptr<EN::Type>> FLOAT "float";
%token <std::weak_ptr<EN::Type>> DOUBLE "double";
%token <std::weak_ptr<EN::Type>> NUMBER "number";
%token <std::weak_ptr<EN::Type>> BOOL "bool";
%token <std::weak_ptr<EN::Type>> CHAR "char";

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
%token <EN::Operator> HOLON_BINARY_OP "<*>"
%token <EN::Operator> HOLON_UNARY_LEFT_OP "*>"
%token <EN::Operator> HOLON_UNARY_RIGHT_OP "<*"

%token <EN::Operator> ASSIGN ":=";
%token <EN::Operator> ASSIGN_PLUS "+=";
%token <EN::Operator> ASSIGN_MINUS "-=";
%token <EN::Operator> ASSIGN_MUL "*=";
%token <EN::Operator> ASSIGN_DIV "/=";
%token <EN::Operator> ASSIGN_MOD "%=";
%token <EN::Operator> ASSIGN_AND "&=";
%token <EN::Operator> ASSIGN_OR "|=";
%token <EN::Operator> ASSIGN_XOR "^=";
%token <EN::Operator> LOGIC_OR "||";
%token <EN::Operator> LOGIC_XOR "^^";
%token <EN::Operator> LOGIC_AND "&&";
%token <EN::Operator> BINARY_OR "|";
%token <EN::Operator> BINARY_XOR "^";
%token <EN::Operator> BINARY_AND "&";
%token <EN::Operator> EQ "==";
%token <EN::Operator> NE "!=";
%token <EN::Operator> LT "<";
%token <EN::Operator> LE "<=";
%token <EN::Operator> GT ">";
%token <EN::Operator> GE ">=";
%token <EN::Operator> SHIFT_LEFT "<<";
%token <EN::Operator> SHIFT_RIGHT ">>";
%token <EN::Operator> PLUS "+";
%token <EN::Operator> MINUS "-";
%token <EN::Operator> MUL "*";
%token <EN::Operator> DIV "/";
%token <EN::Operator> MOD "%";
%token <EN::Operator> LOGIC_NOT "!";
%token <EN::Operator> BINARY_NOT "~";
%token <EN::Operator> INC "++";
%token <EN::Operator> DEC "--";
%token <EN::Operator> DOT ".";
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
%left HOLON_BINARY_OP
%right LOGIC_NOT BINARY_NOT INC DEC HOLON_UNARY_RIGHT_OP HOLON_UNARY_LEFT_OP
%nonassoc APOSTROPHE IS

%type <string> name
%type <std::pair<EN::Visibility, string>> definition_header
%type <EN::Visibility> visibility
%type <std::weak_ptr<EN::Type>> primitive_type
%type <std::weak_ptr<EN::Type>> scalar_primitive_type
// %type <std::weak_ptr<EN::Type>> notification_or_field
%type <std::shared_ptr<EN::Expr>> primary_expr
%type <EN::NotificationParameter> notification_param
%type <EN::AllowedOperations> operation
%type <EN::AllowedOperations> operations
%type <std::list<std::shared_ptr<EN::Edge>>> create_edge
%type <std::list<std::shared_ptr<EN::Expr>>> create_edge_list
%type <std::list<std::shared_ptr<EN::Expr>>> vertex_list
%type <std::list<std::shared_ptr<EN::Expr>>> _vertex_list
%type <std::shared_ptr<EN::Expr>> when_clause
%type <std::shared_ptr<EN::Expr>> with_clause
%type <std::pair<std::shared_ptr<EN::Expr>, std::shared_ptr<EN::Expr>>> edge_function

%type <std::shared_ptr<EN::Expr>> expr
%type <std::shared_ptr<EN::Expr>> binary_expr
%type <EN::Operator> binary_op
%type <std::shared_ptr<EN::Expr>> unary_left
%type <EN::Operator> unary_left_op
%type <std::shared_ptr<EN::Expr>> unary_right
%type <EN::Operator> unary_right_op
%type <std::shared_ptr<EN::Expr>> access

%start program

%%

program : { driver.clear(); } statements

statements : statement statements 
           | %empty

statement : definition
          | "edge" create_edge ";" {
            for (auto edge : $2) driver.graph.addEdge(edge);
          }
          | expr ";"
          | notify ";"
            
definition : vertex_definition

vertex_definition : definition_header "vertex" 
                    {
                        driver.vertexBuilder = EN::VertexBuilder(); 
                        driver.vertexBuilder.setVisibility($1.first); 
                        driver.vertexBuilder.setId($1.second);
                    }
                    vertex_type notification_params vertex_body ";" {
                        graph.addVertex(driver.vertexBuilder.build());
                    }

definition_header : visibility { $$ = {$1, ""};} 
                  | visibility name "is" { $$ = {$1, $2};} 

name : IDENTIFIER | "head" {$$ = "head";}

visibility : "public" | "private" | "declare"

vertex_type : primitive_type {driver.vertexBuilder.setType($1);} | %empty

notification_params : %empty | "(" notification_param param_list ")" {
                        driver.vertexBuilder.addNotificationParameter($2);
                    }

param_list : "," notification_param param_list { driver.vertexBuilder.addNotificationParameter($2); } | %empty

notification_param : IDENTIFIER "is" primitive_type {
                        $$ = EN::NotificationParameter($1, $3);
                    } | IDENTIFIER "is" primitive_type "default" expr {
                        $$ = EN::NotificationParameter($1, $3, $5);
                    }

vertex_body : "," vertex_body_part vertex_body | %empty

vertex_body_part : vertex_state | enabled_ops | initial_value | interfaces | default_edge | create_edge {
            for (auto edge : $1) driver.graph.addEdge(edge);
          }

vertex_state : "state" expr {
    driver.vertexBuilder.setStateExpr($2).setBoundState(false);
} | "state" "bound" expr {
    driver.vertexBuilder.setStateExpr($3).setBoundState(true);
}

enabled_ops : "enables" operations {
    driver.vertexBuilder.setEnabledOperations($2);
} | "disables" operations {
    driver.vertexBuilder.setDisabledOperations($2);
}

operations : operation operations {
    $$ = static_cast<EN::AllowedOperations>($1 | $2);
} | %empty {
    $$ = EN::AllowedOperations::NONE;
}

operation : "read" | "notify" | "listen"

initial_value : "initialise" expr {
    driver.vertexBuilder.setInitialValue($2);
}

interfaces: "implements" interface_list

interface_list : IDENTIFIER | IDENTIFIER interfaces

default_edge : "default" edge_function {
                driver.vertexBuilder.setDefaultWhen($2.first);
                driver.vertexBuilder.setDefaultWith($2.second);
            }

create_edge : create_edge_list "->" create_edge_list edge_function {
    $$ = EN::Edge::createMultipleEdges($1, $3, $4.first, $4.second);
}

create_edge_list : access { $$ = {$1}; } | "[" vertex_list "]" { $$ = $2; }

vertex_list : access _vertex_list { $2.push_front($1); $$ = $2; }

_vertex_list : %empty { $$ = {}; } | "," access _vertex_list { $3.push_front($2); $$ = $3; }

edge_function : when_clause with_clause { $$ = {$1, $2}; }

when_clause : %empty { $$ = nullptr; } | "when" expr { $$ = $2; }
with_clause : %empty { $$ = nullptr; } | "with" expr { $$ = $2; }

primitive_type : scalar_primitive_type | primitive_type "[" expr "]" {
    auto type = graph.typeManager.addArrayType($1, {$3});
}

scalar_primitive_type : "int8" | "int16" | "int24" | "int32" | "int" | "uint8"
                      | "uint16" | "uint24" | "uint32" | "uint" | "float"
                      | "double" | "number" | "bool" | "char"

expr : binary_expr

binary_expr : unary_left | unary_left binary_op binary_expr {
    $$ = std::make_shared<EN::BinaryExpr>($1, $2, $3);
}

binary_op : // IDENTIFIER | 
            ":=" | "+=" | "-=" | "*=" | "/=" | "%=" | "&=" | "|=" | "^="  
            | "||" | "^^" | "&&" | "|"  | "^"  | "&"  | "==" | "!=" | "<" | "<="
            | ">" | ">=" | "<<" | ">>" | "+"  | "-" | "*"  | "/"  | "%" | "<*>"


unary_left : unary_right
            | "*>" unary_left {
                $$ = std::make_shared<EN::UnaryExpr>($1, $2, EN::UnaryExpr::Direction::LEFT);
            }
            | unary_left_op unary_left {
                $$ = std::make_shared<EN::UnaryExpr>($1, $2, EN::UnaryExpr::Direction::LEFT);
            }

unary_left_op : "-" | "!" | "~" | "++" | "--"

unary_right : access 
            | unary_right "<*" {
                $$ = std::make_shared<EN::UnaryExpr>($2, $1, EN::UnaryExpr::Direction::RIGHT);
            }
            | unary_right unary_right_op {
                $$ = std::make_shared<EN::UnaryExpr>($2, $1, EN::UnaryExpr::Direction::RIGHT);
            }

unary_right_op : "++" | "--"

access : primary_expr {
    $$ = $1;
}

/* notification_or_field : %empty
                      | "(" ")" notification_or_field
                      | "(" expr_list ")" notification_or_field
                      | "[" expr "]" notification_or_field */

expr_list :  expr _expr_list
_expr_list : %empty | "," expr _expr_list

primary_expr : SIGNED_INTEGER_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | UNSIGNED_INTEGER_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1); }
             | BOOL_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | CHAR_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | STRING_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | DOUBLE_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | FLOAT_LITERAL {$$ = std::make_shared<EN::LiteralExpr>($1);}
             | name {$$ = std::make_shared<EN::VertexAccessExpr>($1, graph);}
             | "this" "'" {$$ = std::make_shared<EN::VertexAccessExpr>("this'", graph);}
             | "this" {$$ = std::make_shared<EN::VertexAccessExpr>("this", graph);}
             | "(" expr ")" {$$ = $2;}

notify :  "->" access
         | expr_list "->" access


%%

// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc, const string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << @$ << " " << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << loc << endl;
}
