#ifndef HEURISTIC_FACTORY_H
#define HEURISTIC_FACTORY_H

#include "descent.hpp"

enum HeuristicType {
  DESCENT
};

class HeuristicFactory {
private:
  HeuristicFactory() {} // don't instanciate a factory
public:
  static Heuristic* createHeuristic(Solution& initialSolution, HeuristicType type) {
    switch (type) {
    case DESCENT:
      return new Descent(initialSolution);
    default:
      return new Descent(initialSolution);
    }
  }
};

#endif
