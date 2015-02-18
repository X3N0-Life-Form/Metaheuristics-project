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
HeuristicType type = LOCAL_SEARCH;

HeuristicType identifyHeuristicType(string arg) {
  if (arg == string("ls")) {
    return LOCAL_SEARCH;
  } else if (arg == string("metro")) {
    return METRO;
  } else if (arg == string("ts")) {
    return TABU_SEARCH;
  } else {
    return LOCAL_SEARCH;
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
  srand(time(NULL));
  dealWithArgs(argc, argv);
  Solution initial_solution(num_periods, boats);
  cout << "Initial cost = " << initial_solution.getCost() << endl;
  Heuristic* heuristic = HeuristicFactory::createHeuristic(initial_solution, type);
  Solution& final_solution = heuristic->applyHeuristic(); // don't tell the national socialists
  cout << "Final cost: " << final_solution.getCost() << endl;
  delete heuristic;
}
