#ifndef LOCAL_DESCENT_H
#define LOCAL_DESCENT_H

#include "localSearch.hpp"

class LocalDescent : public LocalSearch {
private:
  int prev_cost;
public:
  LocalDescent(Solution& solution) :
    LocalSearch(solution),
    prev_cost(-1) {}

  virtual Solution& applyHeuristic() {
    //int i = 0;
    while (!stop()) {
      Solution current(solution);
      prev_cost = solution.getCost();
      //i++;
      for (int period = 0; period < number_of_periods; period++) {
	for (int target1 = 1; target1 <= (int) boats.size(); target1++) {
	  for (int target2 = 1; target2 <= (int) boats.size(); target2++) {
	    if (target1 == target2) continue;
	    current.moveSwap(period, target1, target2);
	    if (selectionCondition(current)) {
	      cout << "cost was improved by "
		   << solution.getCost() - current.getCost() << endl;
	      validateSwap(period, target1, target2, current);
	    }
	  }
	}
      }
    }
    //cout << "loopcount: " << i << endl;
    return solution;
  }
};

#endif
