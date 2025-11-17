#include "Parameters.h"

namespace Gnocchi {
Parameters::Parameters(const string inputFile, const string outputPath)
    : inputFile{inputFile}, outputPath{outputPath} {}

Parameters::Parameters() {}
} // namespace Gnocchi