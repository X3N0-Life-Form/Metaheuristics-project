#ifndef HEURISTIC_FACTORY_H
#define HEURISTIC_FACTORY_H

#include "localSearch.hpp"
#include "tabuSearch.hpp"
#include "localDescent.hpp"

enum HeuristicType {
  LOCAL_DESCENT,
  LOCAL_SEARCH,
  METRO,
  TABU_SEARCH
};

class HeuristicFactory {
private:
  HeuristicFactory() {} // don't instanciate a factory
public:
  static Heuristic* createHeuristic(Solution& initialSolution, HeuristicType type) {
    switch (type) {
    case LOCAL_SEARCH:
      return new LocalSearch(initialSolution);
    case TABU_SEARCH:
      return new TabuSearch(initialSolution);
    case LOCAL_DESCENT:
      return new LocalDescent(initialSolution);
    default:
      return new LocalSearch(initialSolution);
    }
  }
};

#endif
