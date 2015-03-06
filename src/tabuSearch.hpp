#ifndef TABU_SEARCH_H
#define TABU_SEARCH_H

#include "localSearch.hpp"

class SwapHistory {
public:
	int period;
	int first;
	int second;

	SwapHistory(int period, int first, int second) :
		period(period), first(first), second(second)
	{}

	SwapHistory(const SwapHistory& other) :
		period(other.period), first(other.first), second(other.second)
	{}
};

ostream& operator<<(ostream& out, const SwapHistory& history) {
	out << "SwapHistory: " << history.period << " [" << history.first << " <=> " << history.second << "]" << endl;
	return out;
}

class TabuSearch : public LocalSearch {
private:
  /**
   * period ==> swap
   */
  std::list<SwapHistory> history_swap;
  unsigned int history_max_size;
public:
  TabuSearch(Solution& solution) : LocalSearch(solution),
	  history_max_size(5)
  {}

  virtual Solution& applyHeuristic() {
    return LocalSearch::applyHeuristic();
  }

	virtual bool stop() {
		if (LocalSearch::stop()) {
			if (history_swap.size() == 0) {
				return true;
			} else {
				SwapHistory prev_swap = history_swap.back();
				history_swap.pop_back();
				//cout << "do the previous swap move " << prev_swap << endl;
				solution.moveSwap(prev_swap.period, prev_swap.first, prev_swap.second);
				return false;
			}
		} else {
			return false;
		}
	}

  virtual bool selectionCondition(Solution& current) {
    return current.getCost() <= solution.getCost();
  }

  virtual void validateSwap(int period, int target1, int target2,
			    Solution& current) {
	history_swap.push_back(SwapHistory(period, target1, target2));
	if (history_swap.size() > history_max_size) {
		history_swap.pop_front();
	}
    LocalSearch::validateSwap(period, target1, target2, current);
  }

};

#endif
