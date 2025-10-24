#pragma once

#include "LocationProvider.h"
#include "scanner.h"

#include "parser.hpp"

#include "ENGraph.h"

#include "VertexBuilder.h"

namespace Gnocchi {
using namespace std;
class Interpreter {
public:
  Interpreter(string fileName);

  int parse();

  void clear();

  void switchInputStream(istream *is);

  EN::Graph &getGraph();

  friend class Parser;

  friend class Scanner;

private:
  LocationProvider locationProvider;
  Scanner m_scanner;
  Parser m_parser;
  EN::Graph graph;
  EN::VertexBuilder vertexBuilder;
};

} // namespace Gnocchi
