#ifndef DESCENT_H
#define DESCENT_H

#include "heuristic.hpp"

class Descent : public Heuristic {

public:
  Descent(Solution& solution) : Heuristic(solution) {}
  virtual Solution& applyHeuristic() {
    return solution;
  }

  virtual bool stop() {
    return true;
  }
};

#endif
