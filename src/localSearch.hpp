#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "heuristic.hpp"
#include <iostream>
using namespace std;

class LocalSearch : public Heuristic {
private:
  int prev_cost;
public:
  LocalSearch(Solution& solution) :
    Heuristic(solution),
    prev_cost(-1) {}

  virtual Solution& applyHeuristic() {
    //int i = 0;
    while (!stop()) {
      Solution current(solution);
      prev_cost = solution.getCost();
      //i++;
      int period = rand() % number_of_periods;
      int target1 = rand() % boats.size() + 1;
      int target2 = rand() % boats.size() + 1;
      while (target1 == target2) target1 = rand() % boats.size() + 1;

      current.moveSwap(period, target1, target2);
      if (selectionCondition(current)) {
	cout << "cost was improved by "
	     << solution.getCost() - current.getCost() << endl;
	validateSwap(period, target1, target2, current);
      }
    }
    //cout << "loopcount: " << i << endl;
    return solution;
  }

  virtual bool stop() {
    cout << solution.getCost() << " == "  << prev_cost << "?\n";
    return solution.getCost() == prev_cost;
  }

  virtual bool selectionCondition(Solution& current) {
    return current.getCost() < solution.getCost();
  }

  virtual void validateSwap(int period, int target1, int target2,
			    Solution& current) {
    prev_cost = solution.getCost();
    solution = current;
  }
};

#endif
