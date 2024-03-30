%{
	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;
    using namespace Gnocchi;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() Parser::make_EOF(location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocationCol(yyleng);
	
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Gnocchi_"
%option yylineno

integer_literal   [-+]?[0-9]+
char_literal	'.'
escape_char_literal	'\\.'
string_literal \".*\"
double_literal {integer_literal}\.[0-9]+
float_literal {double_literal}f
identifier      [a-zA-Z\_]([a-zA-Z0-9\_])*
%%

"//".* {
}


edge {
	return Gnocchi::Parser::make_EDGE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

atom {
	return Gnocchi::Parser::make_ATOM(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

this {
	return Gnocchi::Parser::make_THIS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

head {
	return Gnocchi::Parser::make_HEAD(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

public {
	return Gnocchi::Parser::make_PUBLIC(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

private {
	return Gnocchi::Parser::make_PRIVATE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

is {
	return Gnocchi::Parser::make_IS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

vertex {
	return Gnocchi::Parser::make_VERTEX(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

bound {
	return Gnocchi::Parser::make_BOUND(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

default {
	return Gnocchi::Parser::make_DEFAULT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

when {
	return Gnocchi::Parser::make_WHEN(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

with {
	return Gnocchi::Parser::make_WITH(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

enables {
	return Gnocchi::Parser::make_ENABLES(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

disables {
	return Gnocchi::Parser::make_DISABLES(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

notify {
	return Gnocchi::Parser::make_NOTIFY(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

read {
	return Gnocchi::Parser::make_READ(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

listen {
	return Gnocchi::Parser::make_LISTEN(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

initialise {
	return Gnocchi::Parser::make_INITIALISE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

holon {
	return Gnocchi::Parser::make_HOLON(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

int {
	return Gnocchi::Parser::make_INT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

int8 {
	return Gnocchi::Parser::make_INT8(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

int16 {
	return Gnocchi::Parser::make_INT16(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

int24 {
	return Gnocchi::Parser::make_INT24(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

int32 {
	return Gnocchi::Parser::make_INT32(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

uint {
	return Gnocchi::Parser::make_UINT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

uint8 {
	return Gnocchi::Parser::make_UINT8(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

uint16 {
	return Gnocchi::Parser::make_UINT16(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

uint24 {
	return Gnocchi::Parser::make_UINT24(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

uint32 {
	return Gnocchi::Parser::make_UINT32(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

float {
	return Gnocchi::Parser::make_FLOAT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}


double {
	return Gnocchi::Parser::make_DOUBLE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

number {
	return Gnocchi::Parser::make_NUMBER(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

bool {
	return Gnocchi::Parser::make_BOOL(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

char {
	return Gnocchi::Parser::make_CHAR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

ref {
	return Gnocchi::Parser::make_REF(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

to {
	return Gnocchi::Parser::make_TO(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

type {
	return Gnocchi::Parser::make_TYPE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

same {
	return Gnocchi::Parser::make_SAME(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

as {
	return Gnocchi::Parser::make_AS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

";" {
	return Gnocchi::Parser::make_SEMICOLON(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"," {
	return Gnocchi::Parser::make_COMMA(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

":" {
	return Gnocchi::Parser::make_COLON(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"(" {
	return Gnocchi::Parser::make_LPAR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

")" {
	return Gnocchi::Parser::make_RPAR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"[" {
	return Gnocchi::Parser::make_LSBRACKET(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"]" {
	return Gnocchi::Parser::make_RSBRACKET(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"{" {
	return Gnocchi::Parser::make_LCBRACKET(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"}" {

	return Gnocchi::Parser::make_RCBRACKET(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"->" {
	return Gnocchi::Parser::make_NOTIFY_OP(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"..." {
	return Gnocchi::Parser::make_ELLIPSIS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"<>" {
	return Gnocchi::Parser::make_HOLON_OP(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

":=" {
	return Gnocchi::Parser::make_ASSIGN(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"+=" {
	return Gnocchi::Parser::make_ASSIGN_PLUS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"-=" {
	return Gnocchi::Parser::make_ASSIGN_MINUS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"*=" {
	return Gnocchi::Parser::make_ASSIGN_MUL(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"/=" {
	return Gnocchi::Parser::make_ASSIGN_DIV(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"%=" {
	return Gnocchi::Parser::make_ASSIGN_MOD(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"&=" {
	return Gnocchi::Parser::make_ASSIGN_AND(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"|=" {
	return Gnocchi::Parser::make_ASSIGN_OR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"^=" {
	return Gnocchi::Parser::make_ASSIGN_XOR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"||" {
	return Gnocchi::Parser::make_LOGIC_OR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"^^" {
	return Gnocchi::Parser::make_LOGIC_XOR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"&&" {
	return Gnocchi::Parser::make_LOGIC_AND(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"|" {
	return Gnocchi::Parser::make_BINARY_OR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"^" {
	return Gnocchi::Parser::make_BINARY_XOR(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"&" {
	return Gnocchi::Parser::make_BINARY_AND(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"==" {
	return Gnocchi::Parser::make_EQ(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"!=" {
	return Gnocchi::Parser::make_NE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"<" {
	return Gnocchi::Parser::make_LT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"<=" {
	return Gnocchi::Parser::make_LE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

">" {
	return Gnocchi::Parser::make_GT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

">=" {
	return Gnocchi::Parser::make_GE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"<<" {
	return Gnocchi::Parser::make_SHIFT_LEFT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

">>" {
	return Gnocchi::Parser::make_SHIFT_RIGHT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"+" {
	return Gnocchi::Parser::make_PLUS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"-" {
	return Gnocchi::Parser::make_MINUS(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"*" {
	return Gnocchi::Parser::make_MUL(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"/" {
	return Gnocchi::Parser::make_DIV(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"%" {
	return Gnocchi::Parser::make_MOD(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"!" {
	return Gnocchi::Parser::make_LOGIC_NOT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"~" {
	return Gnocchi::Parser::make_BINARY_NOT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"++" {
	return Gnocchi::Parser::make_INC(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"--" {
	return Gnocchi::Parser::make_DEC(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"." {
	return Gnocchi::Parser::make_DOT(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}


"'" {
	return Gnocchi::Parser::make_APOSTROPHE(Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

[\n] { 
	m_driver.increaseLocationCol(-m_driver.getLocationCol() + 1);
}

[\t ] {
}

{integer_literal} {
	int integer = std::atoi(yytext);
	return Gnocchi::Parser::make_INTEGER_LITERAL(integer, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"true" {
	return Gnocchi::Parser::make_BOOL_LITERAL(true, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

"false" {
	return Gnocchi::Parser::make_BOOL_LITERAL(false, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

{char_literal} {
	return Gnocchi::Parser::make_CHAR_LITERAL(yytext[1], Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

{escape_char_literal} {
    char escape_char;
    switch(yytext[2]) {
        case '\'':
            escape_char = '\'';
            break;
        case '\"':
            escape_char = '\"';
            break;
        case '?':
            escape_char = '?';
            break;
        case '\\':
            escape_char = '\\';
            break;
        case 'a':
            escape_char = '\a';
            break;
        case 'b':
            escape_char = '\b';
            break;
        case 'f':
            escape_char = '\f';
            break;
        case 'n':
            escape_char = '\n';
            break;
        case 'r':
            escape_char = '\r';
            break;
        case 't':
            escape_char = '\t';
            break;
        case 'v':
            escape_char = '\v';
            break;
        case '0':
            escape_char = '\0';
            break;
        default:
            LexerError("unrecognized scape character!");
    }
    return Gnocchi::Parser::make_CHAR_LITERAL(escape_char, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

{string_literal} {
	return Gnocchi::Parser::make_STRING_LITERAL(yytext, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

{double_literal} {
	double value = std::stod(yytext);
	return Gnocchi::Parser::make_DOUBLE_LITERAL(value, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

{float_literal} {
	float value = std::atof(yytext);
	return Gnocchi::Parser::make_FLOAT_LITERAL(value, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}


{identifier} {
    return Gnocchi::Parser::make_IDENTIFIER(yytext, Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));
}

. {
	cerr << "line " << yylineno << ": illegal character '" << yytext[0] << endl;
}
            
<<EOF>> {
    return yyterminate();
}


%%
