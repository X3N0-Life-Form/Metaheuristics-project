#ifndef DESCENT_H
#define DESCENT_H

#include "heuristic.hpp"

class LocalSearch : public Heuristic {
public:
  LocalSearch(Solution& solution) : Heuristic(solution) {}

  virtual Solution& applyHeuristic() {
    while (!stop()) {
      Solution current(solution);
      current.moveHost();
      if (current.getCost() <= solution.getCost()) {
	//solution = current;
      }
    }
    return solution;
  }

  virtual bool stop() {
    return false;
  }
};

#endif
