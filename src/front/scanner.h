#pragma once

/**
 * Generated Flex class name is yyFlexLexer by default. If we want to use more flex-generated
 * classes we should name them differently. See scanner.l prefix option.
 *
 * Unfortunately the implementation relies on this trick with redefining class name
 * with a preprocessor macro. See GNU Flex manual, "Generating C++ Scanners" section
 */
#if !defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer Gnocchi_FlexLexer // the trick with prefix; no namespace here :(

#include "FlexLexer.h"

#endif

// Scanner method signature is defined by this macro. Original yylex() returns int.
// Sinice Bison 3 uses symbol_type, we must change returned type. We also rename it
// to something sane, since you cannot overload return type.
#undef YY_DECL
#define YY_DECL Gnocchi::Parser::symbol_type Gnocchi::Scanner::get_next_token()

#include "parser.hpp" // this is needed for symbol_type

#include "LocationProvider.h"

namespace Gnocchi
{
  using namespace std;

  class LexicalException : runtime_error
  {

  public:
    LexicalException(string msg) : runtime_error(msg) {}
  };

  class Scanner : public yyFlexLexer
  {
  public:
    Scanner(LocationProvider &driver) : m_driver(driver) {}

    virtual ~Scanner() {}

    virtual Gnocchi::Parser::symbol_type get_next_token();

    virtual void LexerError(const char *msg)
    {
      throw LexicalException(msg);
    }

    string parseString(char *text);

    static char getEscapeChar(char c);

  private:
    LocationProvider &m_driver;
  };

}