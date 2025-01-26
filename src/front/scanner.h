/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

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