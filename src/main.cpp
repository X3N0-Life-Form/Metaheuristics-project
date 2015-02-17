#include <iostream>
#include <vector>
#include "boat.h"
#include "utils.h"

using namespace std;

vector<Boat> boats;


void dealWithArgs(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == string("--file")) {
      parse(string(argv[++i]), boats);
    } else {
      cout << "Unrecognised Argument: " << argv[i] << endl;
    }
  }
}


int main(int argc, char** argv) {
  dealWithArgs(argc, argv);
}
