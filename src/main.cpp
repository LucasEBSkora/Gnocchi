#include "interpreter.h"
#include "parser.hpp"
#include <iostream>

using namespace Gnocchi;
using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: Gnocchi <in-file> \n"
         << "where in-file is the source file to compile" << endl;
    return -1;
  }

  Interpreter i{argv[1]};
  ifstream file(argv[1]);
  i.switchInputStream(&file);
  int res = i.parse();
  if (res == 0) {
  }

  return res;
}
