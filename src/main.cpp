#include <iostream>
#include <vector>
#include "boat.h"
#include "utils.h"
#include "solution.h"

using namespace std;

vector<Boat> boats;
int num_periods = 8;

void dealWithArgs(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == string("--file")) {
      parse(string(argv[++i]), boats);
    } else if (string(argv[i]) == string("--periods")) {
      num_periods = stoi(argv[++i]);
    } else {
      cout << "Unrecognised Argument: " << argv[i] << endl;
    }
  }
}


int main(int argc, char** argv) {
  dealWithArgs(argc, argv);
  Solution initial_solution(num_periods, boats);
  cout << initial_solution << endl;
}
