#include "ParametersParser.h"
#include "interpreter.h"
#include "parser.hpp"

using namespace Gnocchi;
using namespace std;

int main(int argc, const char **argv) {

  ParametersParser parser;
  int ret = parser.parse(argc, argv);
  if (ret != 0) {
    return ret;
  }
  Parameters params = parser.getParameters();
  Interpreter i{params.inputFile};
  ifstream file(params.inputFile);
  i.switchInputStream(&file);
  int res = i.parse();
  if (res != 0) {
    return res;
  }

  return 0;
}
