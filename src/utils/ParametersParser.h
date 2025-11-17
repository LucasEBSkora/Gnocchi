#pragma once

#include "Parameters.h"

namespace Gnocchi {
class ParametersParser {
public:
  ParametersParser();
  int parse(int argc, const char **argv);
  Parameters getParameters() const;

private:
  void printUsageInformation() const;
  Parameters params;
  string inputFile;
  string outputPath;
};
} // namespace Gnocchi