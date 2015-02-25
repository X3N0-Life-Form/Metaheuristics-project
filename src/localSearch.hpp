#ifndef LOCAL_SEARCH_H
#define LOCAL_SEARCH_H

#include "localDescent.hpp"


class LocalSearch : public LocalDescent {
protected:
  double probability;
  double proba_growth;
public:
  LocalSearch(Solution& solution) :
    LocalDescent(solution),
    probability(0.05),
    proba_growth(0.1)
  {}

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
	//cout << "cost was improved by "
	//     << solution.getCost() - current.getCost() << endl;
	validateSwap(period, target1, target2, current);
      }
    }
    //cout << "loopcount: " << i << endl;
    return solution;
  }
  virtual bool stop() {
    if (solution.getCost() < prev_cost) {
      return false;
    }
    double roll = rand();
    //cout << roll << " < " << probability << "?\n";
    if (roll < probability) {
      return true;
    } else {
      probability *= 1 + proba_growth;
      //cout << "new probability: " << probability << endl;
      return false;
    }
  }
};

#endif
