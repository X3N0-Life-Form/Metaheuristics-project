#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include "localSearch.hpp"

#define SWAP_HISTORY(p, t1, t2) std::pair<int, std::pair<int, int> >(p, std::pair<int, int>(t1, t2))

class TabuSearch : public LocalSearch {
private:
  /**
   * period ==> swap
   */
  std::list<std::pair<int, std::pair<int, int> > > history_swap;
public:
  TabuSearch(Solution& solution) : LocalSearch(solution) {}

  virtual Solution& applyHeuristic() {
    return LocalSearch::applyHeuristic();
  }

  virtual bool stop() {
    return false;
  }

  virtual bool selectionCondition(Solution& current) {
    return current.getCost() <= solution.getCost();
  }

  virtual void validateSwap(int period, int target1, int target2,
			    Solution& current) {
    history_swap.push_back(SWAP_HISTORY(period, target1, target2));
    LocalSearch::validateSwap(period, target1, target2, current);
  }

};

#endif
