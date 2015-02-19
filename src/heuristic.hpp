#ifndef HEURISTIC_H
#define HEURISTIC_H

#include "solution.h"

class Heuristic {
 protected:
  Solution& solution;
  int number_of_periods;
  std::vector<Boat>& boats;
 public:
  Heuristic(Solution& solution) :
    solution(solution),
    number_of_periods(solution.getNumber_of_periods()),
    boats(solution.getBoats()) {}
  virtual ~Heuristic() {}
  virtual Solution& applyHeuristic() = 0;
  virtual bool stop() = 0;
};

#endif
