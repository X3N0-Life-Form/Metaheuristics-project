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
      for (int period = 0; period < number_of_periods; period++) {
	for (int target1 = 1; target1 <= (int) boats.size(); target1++) {
	  for (int target2 = 1; target2 <= (int) boats.size(); target2++) {
	    if (target1 == target2) continue;
	    current.moveSwap(period, target1, target2);
	    if (current.getCost() < solution.getCost()) {
	      cout << "cost was improved by "
		   << solution.getCost() - current.getCost() << endl;
	      prev_cost = solution.getCost();
	      solution = current;
	    }
	  }
	}
      }
    }
    //cout << "loopcount: " << i << endl;
    return solution;
  }

  virtual bool stop() {
    cout << solution.getCost() << " == "  << prev_cost << "?\n";
    return solution.getCost() == prev_cost;
  }
};

#endif
