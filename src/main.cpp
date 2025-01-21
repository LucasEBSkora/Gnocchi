#include <iostream>
#include "scanner.h"
#include "parser.hpp"
#include "interpreter.h"

using namespace Gnocchi;
using namespace std;

int main(int argc, char **argv) {

  if (argc != 3) {
    std::cerr << "Usage: Gnocchi <in-file> <out-file>\n"
              << "where in-file  is source file to compile and out-file is the name of the assembly file" << std::endl;
    return -1;
  }

  Interpreter i{argv[1]};
  std::ifstream file(argv[1]);
  i.switchInputStream(&file);
  int res = i.parse();
  if (res == 0) {
  }

  return res;
}
