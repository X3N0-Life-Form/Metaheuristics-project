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
  virtual bool selectionCondition(Solution& current) = 0;
  virtual void validateSwap(int period, int target1, int target2,
			    Solution& current) = 0;
};

#endif
