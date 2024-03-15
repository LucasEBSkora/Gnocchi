%{
	#include <iostream>
	#include <cstdlib>
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

integer_value   [-+]?[0-9]+
identifier      [a-zA-Z\_]([a-zA-Z0-9\_])*
%%

"//".* {
}

declare {
}


delete {
}


if {
}


while {
}


"[" {
}

"]" {
}

"{" {
}

"}" {
}


\+ {
}

\- {
}

= {
}


== {
}

!= {
}

\> {
}

">=" {
}

\< {
}

"<=" {
}
         
\( {
}
            
\) { 
}
            
";" {
}
         
[\n] { 
}

[\t ] {
}

{integer_value} {
}

{identifier} {
}

. {
}
            
<<EOF>> {
    return yyterminate();
}


%%
