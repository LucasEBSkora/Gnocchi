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

#include "interpreter.h"

#include <sstream>

using namespace Gnocchi;

Interpreter::Interpreter(std::string filename) : m_scanner(*this),
                                                 m_parser(m_scanner, *this/*, stmts*/),
                                                 m_location_col(0),
                                                 fileName{filename}
{
}

int Interpreter::parse()
{
    m_location_col = 0;
    return m_parser.parse();
}

void Interpreter::clear()
{
    m_location_col = 0;
}

void Interpreter::switchInputStream(std::istream *is)
{
    m_scanner.switch_streams(is, NULL);
}

// std::vector<Statement *>& Interpreter::getStmts()
// {
//     return stmts;
// }

void Interpreter::increaseLocationCol(unsigned int loc)
{
    m_location_col += loc;
}

unsigned int Interpreter::getLocationCol() const
{
    return m_location_col;
}

std::string *Interpreter::getFileName()
{
    return &fileName;
}