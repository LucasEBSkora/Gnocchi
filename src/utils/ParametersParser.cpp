#include "ParametersParser.h"
#include "Parameters.h"
#include <cstring>
#include <iostream>

using std::cerr;
using std::endl;

namespace Gnocchi {
ParametersParser::ParametersParser()
    : inputFile{""}, // if the input parameter is empty, it should be an error
      outputPath{""} // The default output parameter is target-dependant
{}

int ParametersParser::parse(int argc, const char **argv) {
  int i = 1;
  while (i < argc - 1) {
    const char *arg = argv[i];
    if (0 == strcmp(arg, "-o") || 0 == strcmp(arg, "--output-path")) {
      ++i;
      if (i >= argc - 1) {
        cerr << "missing output path\n";
        printUsageInformation();
        return -i;
      }
      outputPath = argv[i];
    } else if (0 == strcmp(arg, "-h") || 0 == strcmp(arg, "--help")) {
      printUsageInformation();
      return -1;
    } else {
      if (arg[0] == '-') {
        cerr << "unrecognized option \"" << arg << "\"\n";
      } else {
        cerr << "unexpected parameter \"" << arg << "\"\n";
      }

      printUsageInformation();
      return -i;
    }
    ++i;
  }
  if (i >= argc) {
    cerr << "missing input file path\n";
    printUsageInformation();
    return -1;
  }
  if (0 == strcmp(argv[i], "-h") || 0 == strcmp(argv[i], "--help")) {
    printUsageInformation();
    return -1;
  }
  inputFile = argv[i];
  return 0;
}

Parameters ParametersParser::getParameters() const { return Parameters(inputFile, outputPath); }

void ParametersParser::printUsageInformation() const {
  cerr << "Usage: Gnocchi <OPTIONS> <in-file> \n"
       << "where in-file is the main source file to compile" << endl;
}
} // namespace Gnocchi