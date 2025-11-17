#pragma once

#include <string>
using std::string;

namespace Gnocchi {
struct Parameters {
  Parameters(const string inputFile, const string outputPath);
  Parameters();
  const string inputFile;
  const string outputPath;
};
} // namespace Gnocchi