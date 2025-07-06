#pragma once

namespace EN {
enum class Operator {
  BINARY_HOLON_OP,      // <*>
  UNARY_LEFT_HOLON_OP,  // *>
  UNARY_RIGHT_HOLON_OP, // <*
  ASSIGN,               // :=
  ASSIGN_PLUS,          // +=
  ASSIGN_MINUS,         // -=
  ASSIGN_MUL,           // *=
  ASSIGN_DIV,           // /=
  ASSIGN_MOD,           // %=
  ASSIGN_AND,           // &=
  ASSIGN_OR,            // |=
  ASSIGN_XOR,           // ^=
  LOGIC_OR,             // ||
  LOGIC_XOR,            // ^^
  LOGIC_AND,            // &&
  BINARY_OR,            // |
  BINARY_XOR,           // ^
  BINARY_AND,           // &
  EQ,                   // ==
  NE,                   // !=
  LT,                   // <
  LE,                   // <=
  GT,                   // >
  GE,                   // >=
  SHIFT_LEFT,           // <<
  SHIFT_RIGHT,          // >>
  PLUS,                 // +
  MINUS,                // -
  MUL,                  // *
  DIV,                  // /
  MOD,                  // %
  LOGIC_NOT,            // !
  BINARY_NOT,           // ~
  INC,                  // ++
  DEC,                  // --
};
}