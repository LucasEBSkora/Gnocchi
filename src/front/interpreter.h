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

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "scanner.h"

#include "parser.hpp"

namespace Gnocchi {

class Interpreter
{
public:
    Interpreter(std::string fileName);
    
    int parse();
    
    void clear();
    
    void switchInputStream(std::istream *is);

    friend class Parser;
    friend class Scanner;
    
protected:
    // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocationCol(unsigned int loc);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int getLocationCol() const;

    std::string* getFileName();

private:
    Scanner m_scanner;
    Parser m_parser;
    unsigned int m_location_col;
    std::string fileName;
};

}

#endif // INTERPRETER_H
