#include "interpreter.h"

using namespace Gnocchi;

Interpreter::Interpreter(string filename)
    : locationProvider{filename}, m_scanner(locationProvider),
      m_parser(m_scanner, *this, graph) {}

int Interpreter::parse() {
  locationProvider.reset();
  return m_parser.parse();
}

void Interpreter::clear() { locationProvider.reset(); }

void Interpreter::switchInputStream(istream *is) {
  m_scanner.switch_streams(is, NULL);
}
