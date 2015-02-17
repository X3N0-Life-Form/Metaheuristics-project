#ifndef DESCENT_H
#define DESCENT_H

#include "heuristic.hpp"

class LocalSearch : public Heuristic {
public:
  LocalSearch(Solution& solution) : Heuristic(solution) {}
  virtual Solution& applyHeuristic() {
    return solution;
  }

  virtual bool stop() {
    return true;
  }
};

#endif
