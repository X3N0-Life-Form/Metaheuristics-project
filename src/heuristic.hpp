#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "solution.h"

class Heuristic {
 protected:
  Solution& solution;

 public:
  Heuristic(Solution& solution) : solution(solution) {}
  virtual ~Heuristic() {}
  virtual Solution& applyHeuristic() = 0;
  virtual bool stop() = 0;
};

#endif
