//
// Created by skora on 20/04/2024.
//

#include "scanner.h"

#include <string>
#include <cstring>

namespace Gnocchi {
  std::string Scanner::parseString(char *text) {
    std::string str{yytext + 1, strlen(yytext) - 2};
    for (size_t i = 0; i < str.size(); ++i) {
      char current = str[i];
      if (current == '\n') {
        m_driver.increaseLocationCol(1);
        continue;
      }
      if (current == '\\') {
        if (i + 1 >= str.size()) continue;
        char next = str[i + 1];
        char escape_char = getEscapeChar(next);
        if (next == -1) continue;
        str.replace(i, 2, std::string{escape_char});
      }
    }

    return str;
  }

  char Scanner::getEscapeChar(char c) {
    switch (c) {
      case '\'':
        return '\'';
      case '\"':
        return '\"';
      case '\\':
        return '\\';
      case 'a':
        return '\a';
      case 'b':
        return '\b';
      case 'f':
        return '\f';
      case 'n':
        return '\n';
      case 'r':
        return '\r';
      case 't':
        return '\t';
      case 'v':
        return '\v';
      case '0':
        return '\0';
      default:
        return -1;
    }
  }
}
