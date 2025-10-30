%{
	#include <iostream>
	#include <cstdlib>
	#include <string>
	#include <cmath>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"
	#include "PrimitiveType.h"

	using namespace std;
    using namespace Gnocchi;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() Parser::make_EOF(location(m_driver.getFileName(), yylineno, m_driver.getLocationCol()));

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocationCol(yyleng);
	
	#define getLoc() Gnocchi::location(m_driver.getFileName(), yylineno, m_driver.getLocationCol())
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Gnocchi_"
%option yylineno

unsigned_integer_literal [0-9]+
unsigned_integer_binary_literal 0b[0-1]+
unsigned_integer_octal_literal 0o[0-7]+
unsigned_integer_hex_literal 0x[0-9a-fA-F]+
unsigned_integer_literal_exponent [0-9]+[eE][0-9]{1,2}
signed_integer_literal_exponent [-+]{unsigned_integer_literal_exponent}
signed_integer_literal   [-+]{unsigned_integer_literal}
char_literal	'.'
escape_char_literal	'\\.'
string_literal \".*\"
double_literal [-+]?[0-9]+\.[0-9]+
exponent_double_literal {double_literal}[eE][-+]?[0-9]+
float_literal {double_literal}f
exponent_float_literal {exponent_double_literal}f
identifier      [a-zA-Z\_]([a-zA-Z0-9\_])*
%%

"//".* {
}


edge {
	return Gnocchi::Parser::make_EDGE(getLoc());
}

atom {
	return Gnocchi::Parser::make_ATOM(getLoc());
}

this {
	return Gnocchi::Parser::make_THIS(getLoc());
}

head {
	return Gnocchi::Parser::make_HEAD(getLoc());
}

public {
	return Gnocchi::Parser::make_PUBLIC(EN::Visibility::PUBLIC, getLoc());
}

private {
	return Gnocchi::Parser::make_PRIVATE(EN::Visibility::PRIVATE, getLoc());
}

declare {
	return Gnocchi::Parser::make_DECLARE(EN::Visibility::DEFAULT, getLoc());
}

is {
	return Gnocchi::Parser::make_IS(getLoc());
}

vertex {
	return Gnocchi::Parser::make_VERTEX(getLoc());
}

state {
	return Gnocchi::Parser::make_STATE(getLoc());
}

bound {
	return Gnocchi::Parser::make_BOUND(getLoc());
}

default {
	return Gnocchi::Parser::make_DEFAULT(getLoc());
}

when {
	return Gnocchi::Parser::make_WHEN(getLoc());
}

with {
	return Gnocchi::Parser::make_WITH(getLoc());
}

enables {
	return Gnocchi::Parser::make_ENABLES(getLoc());
}

disables {
	return Gnocchi::Parser::make_DISABLES(getLoc());
}

notify {
	return Gnocchi::Parser::make_NOTIFY(EN::AllowedOperations::NOTIFY, getLoc());
}

read {
	return Gnocchi::Parser::make_READ(EN::AllowedOperations::READ,getLoc());
}

listen {
	return Gnocchi::Parser::make_LISTEN(EN::AllowedOperations::LISTEN,getLoc());
}

initialise {
	return Gnocchi::Parser::make_INITIALISE(getLoc());
}

implements {
	return Gnocchi::Parser::make_IMPLEMENTS(getLoc());
}

holon {
	return Gnocchi::Parser::make_HOLON(getLoc());
}

int {
	return Gnocchi::Parser::make_INT(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT), getLoc());
}

int8 {
	return Gnocchi::Parser::make_INT8(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT8), getLoc());
}

int16 {
	return Gnocchi::Parser::make_INT16(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT16), getLoc());
}

int24 {
	return Gnocchi::Parser::make_INT24(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT24), getLoc());
}

int32 {
	return Gnocchi::Parser::make_INT32(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::INT32), getLoc());
}

uint {
	return Gnocchi::Parser::make_UINT(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::UINT), getLoc());
}

uint8 {
	return Gnocchi::Parser::make_UINT8(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::UINT8), getLoc());
}

uint16 {
	return Gnocchi::Parser::make_UINT16(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::UINT16), getLoc());
}

uint24 {
	return Gnocchi::Parser::make_UINT24(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::UINT24), getLoc());
}

uint32 {
	return Gnocchi::Parser::make_UINT32(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::UINT32), getLoc());
}

float {
	return Gnocchi::Parser::make_FLOAT(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::FLOAT), getLoc());
}

double {
	return Gnocchi::Parser::make_DOUBLE(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::DOUBLE), getLoc());
}

number {
	return Gnocchi::Parser::make_NUMBER(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::NUMBER), getLoc());
}

bool {
	return Gnocchi::Parser::make_BOOL(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::BOOL), getLoc());
}

char {
	return Gnocchi::Parser::make_CHAR(EN::PrimitiveType::getPrimitiveType(EN::PrimitiveType::CHAR), getLoc());
}

ref {
	return Gnocchi::Parser::make_REF(getLoc());
}

to {
	return Gnocchi::Parser::make_TO(getLoc());
}

type {
	return Gnocchi::Parser::make_TYPE(getLoc());
}

same {
	return Gnocchi::Parser::make_SAME(getLoc());
}

as {
	return Gnocchi::Parser::make_AS(getLoc());
}

";" {
	return Gnocchi::Parser::make_SEMICOLON(getLoc());
}

"," {
	return Gnocchi::Parser::make_COMMA(getLoc());
}

":" {
	return Gnocchi::Parser::make_COLON(getLoc());
}

"(" {
	return Gnocchi::Parser::make_LPAR(getLoc());
}

")" {
	return Gnocchi::Parser::make_RPAR(getLoc());
}

"[" {
	return Gnocchi::Parser::make_LSBRACKET(getLoc());
}

"]" {
	return Gnocchi::Parser::make_RSBRACKET(getLoc());
}

"{" {
	return Gnocchi::Parser::make_LCBRACKET(getLoc());
}

"}" {

	return Gnocchi::Parser::make_RCBRACKET(getLoc());
}

"->" {
	return Gnocchi::Parser::make_NOTIFY_OP(getLoc());
}

"..." {
	return Gnocchi::Parser::make_ELLIPSIS(getLoc());
}

"<*>" {
	return Gnocchi::Parser::make_HOLON_BINARY_OP(EN::Operator::BINARY_HOLON_OP, getLoc());
}

"*>" {
	return Gnocchi::Parser::make_HOLON_UNARY_LEFT_OP(EN::Operator::UNARY_LEFT_HOLON_OP, getLoc());
}

"<*" {
	return Gnocchi::Parser::make_HOLON_UNARY_RIGHT_OP(EN::Operator::UNARY_RIGHT_HOLON_OP, getLoc());
}

":=" {
	return Gnocchi::Parser::make_ASSIGN(EN::Operator::ASSIGN, getLoc());
}

"+=" {
	return Gnocchi::Parser::make_ASSIGN_PLUS(EN::Operator::ASSIGN_PLUS, getLoc());
}

"-=" {
	return Gnocchi::Parser::make_ASSIGN_MINUS(EN::Operator::ASSIGN_MINUS, getLoc());
}

"*=" {
	return Gnocchi::Parser::make_ASSIGN_MUL(EN::Operator::ASSIGN_MUL, getLoc());
}

"/=" {
	return Gnocchi::Parser::make_ASSIGN_DIV(EN::Operator::ASSIGN_DIV, getLoc());
}

"%=" {
	return Gnocchi::Parser::make_ASSIGN_MOD(EN::Operator::ASSIGN_MOD, getLoc());
}

"&=" {
	return Gnocchi::Parser::make_ASSIGN_AND(EN::Operator::ASSIGN_AND, getLoc());
}

"|=" {
	return Gnocchi::Parser::make_ASSIGN_OR(EN::Operator::ASSIGN_OR, getLoc());
}

"^=" {
	return Gnocchi::Parser::make_ASSIGN_XOR(EN::Operator::ASSIGN_XOR, getLoc());
}

"||" {
	return Gnocchi::Parser::make_LOGIC_OR(EN::Operator::LOGIC_OR, getLoc());
}

"^^" {
	return Gnocchi::Parser::make_LOGIC_XOR(EN::Operator::LOGIC_XOR, getLoc());
}

"&&" {
	return Gnocchi::Parser::make_LOGIC_AND(EN::Operator::LOGIC_AND, getLoc());
}

"|" {
	return Gnocchi::Parser::make_BINARY_OR(EN::Operator::BINARY_OR, getLoc());
}

"^" {
	return Gnocchi::Parser::make_BINARY_XOR(EN::Operator::BINARY_XOR, getLoc());
}

"&" {
	return Gnocchi::Parser::make_BINARY_AND(EN::Operator::BINARY_AND, getLoc());
}

"==" {
	return Gnocchi::Parser::make_EQ(EN::Operator::EQ, getLoc());
}

"!=" {
	return Gnocchi::Parser::make_NE(EN::Operator::NE, getLoc());
}

"<" {
	return Gnocchi::Parser::make_LT(EN::Operator::LT, getLoc());
}

"<=" {
	return Gnocchi::Parser::make_LE(EN::Operator::LE, getLoc());
}

">" {
	return Gnocchi::Parser::make_GT(EN::Operator::GT, getLoc());
}

">=" {
	return Gnocchi::Parser::make_GE(EN::Operator::GE, getLoc());
}

"<<" {
	return Gnocchi::Parser::make_SHIFT_LEFT(EN::Operator::SHIFT_LEFT, getLoc());
}

">>" {
	return Gnocchi::Parser::make_SHIFT_RIGHT(EN::Operator::SHIFT_RIGHT, getLoc());
}

"+" {
	return Gnocchi::Parser::make_PLUS(EN::Operator::PLUS, getLoc());
}

"-" {
	return Gnocchi::Parser::make_MINUS(EN::Operator::MINUS, getLoc());
}

"*" {
	return Gnocchi::Parser::make_MUL(EN::Operator::MUL, getLoc());
}

"/" {
	return Gnocchi::Parser::make_DIV(EN::Operator::DIV, getLoc());
}

"%" {
	return Gnocchi::Parser::make_MOD(EN::Operator::MOD, getLoc());
}

"!" {
	return Gnocchi::Parser::make_LOGIC_NOT(EN::Operator::LOGIC_NOT, getLoc());
}

"~" {
	return Gnocchi::Parser::make_BINARY_NOT(EN::Operator::BINARY_NOT, getLoc());
}

"++" {
	return Gnocchi::Parser::make_INC(EN::Operator::INC, getLoc());
}

"--" {
	return Gnocchi::Parser::make_DEC(EN::Operator::DEC, getLoc());
}

"." {
	return Gnocchi::Parser::make_DOT(EN::Operator::LE, getLoc());
}


"'" {
	return Gnocchi::Parser::make_APOSTROPHE(getLoc());
}

[\n] { 
	m_driver.increaseLocationCol(-m_driver.getLocationCol() + 1);
}

[\t ] {
}

{signed_integer_literal} {
	long long integer = atoll(yytext);
	return Gnocchi::Parser::make_SIGNED_INTEGER_LITERAL(integer, getLoc());
}

{unsigned_integer_literal} {
	unsigned long long integer = strtoull(yytext, nullptr, 10);
	return Gnocchi::Parser::make_UNSIGNED_INTEGER_LITERAL(integer, getLoc());
}

{unsigned_integer_binary_literal} {
	unsigned long long integer = strtoull(yytext + 2, nullptr, 2);
	return Gnocchi::Parser::make_UNSIGNED_INTEGER_LITERAL(integer, getLoc());
}

{unsigned_integer_octal_literal} {
	unsigned long long integer = strtoull(yytext + 2, nullptr, 8);
	return Gnocchi::Parser::make_UNSIGNED_INTEGER_LITERAL(integer, getLoc());
}

{unsigned_integer_hex_literal} {
	unsigned long long integer = strtoull(yytext + 2, nullptr, 16);
	return Gnocchi::Parser::make_UNSIGNED_INTEGER_LITERAL(integer, getLoc());
}

{unsigned_integer_literal_exponent} {
	char* exp;
	unsigned long long integer = strtoull(yytext, &exp, 10);
	integer *= pow(10, strtoull(exp+1, nullptr, 10));
	return Gnocchi::Parser::make_UNSIGNED_INTEGER_LITERAL(integer, getLoc());
}

{signed_integer_literal_exponent} {
	char* exp;
	long long integer = strtoll(yytext, &exp, 10);
	integer *= pow(10, strtoll(exp+1, nullptr, 10));
	return Gnocchi::Parser::make_SIGNED_INTEGER_LITERAL(integer, getLoc());
}

"true" {
	return Gnocchi::Parser::make_BOOL_LITERAL(true, getLoc());
}

"false" {
	return Gnocchi::Parser::make_BOOL_LITERAL(false, getLoc());
}

{char_literal} {
	return Gnocchi::Parser::make_CHAR_LITERAL(yytext[1], getLoc());
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
    return Gnocchi::Parser::make_CHAR_LITERAL(escape_char, getLoc());
}

{string_literal} {
	return Gnocchi::Parser::make_STRING_LITERAL(parseString(yytext), getLoc());
}

{double_literal} {
	double value = stod(yytext);
	return Gnocchi::Parser::make_DOUBLE_LITERAL(value, getLoc());
}

{exponent_double_literal} {
	char* exp;
	double value = strtod(yytext, &exp);
	value *= pow(10, strtod(exp+1, nullptr));
	return Gnocchi::Parser::make_DOUBLE_LITERAL(value, getLoc());
}

{float_literal} {
	float value = atof(yytext);
	return Gnocchi::Parser::make_FLOAT_LITERAL(value, getLoc());
}

{exponent_float_literal} {
	char* exp;
	float value = strtof(yytext, &exp);
	value *= pow(10, strtof(exp+1, nullptr));
	return Gnocchi::Parser::make_FLOAT_LITERAL(value, getLoc());
}

{identifier} {
    return Gnocchi::Parser::make_IDENTIFIER(yytext, getLoc());
}

. {
	cerr << "line " << yylineno << ": illegal character '" << yytext[0] << endl;
}
            
<<EOF>> {
    return yyterminate();
}


%%
