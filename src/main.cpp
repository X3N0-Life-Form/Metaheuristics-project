#include <iostream>
#include <vector>
#include "boat.h"
#include "utils.h"
#include "solution.h"
#include "heuristic.hpp"
#include "heuristicFactory.hpp"

using namespace std;

vector<Boat> boats;
int num_periods = 8;
HeuristicType type = DESCENT;

HeuristicType identifyHeuristicType(string arg) {
  if (arg == string("descent")) {
    return DESCENT;
  } else {
    return DESCENT;
  }
}

void dealWithArgs(int argc, char** argv) {
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == string("--file")) {
      parse(string(argv[++i]), boats);
    } else if (string(argv[i]) == string("--periods")) {
      num_periods = stoi(argv[++i]);
    } else if (string(argv[i]) == string("--heuristic")) {
      type = identifyHeuristicType(argv[++i]);
    } else {
      cout << "Unrecognised Argument: " << argv[i] << endl;
    }
  }
}


int main(int argc, char** argv) {
  dealWithArgs(argc, argv);
  Solution initial_solution(num_periods, boats);
  cout << "Initial cost = " << initial_solution.getCost() << endl;
  Heuristic* heuristic = HeuristicFactory::createHeuristic(initial_solution, type);
  Solution& final_solution = heuristic->applyHeuristic(); // don't tell the national socialists
  cout << final_solution << endl;
  delete heuristic;
}
