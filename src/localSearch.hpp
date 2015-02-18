#ifndef DESCENT_H
#define DESCENT_H

#include "heuristic.hpp"
#include <iostream>
using namespace std;

class LocalSearch : public Heuristic {
private:
  bool b_stop;
public:
  LocalSearch(Solution& solution) : Heuristic(solution), b_stop(false) {}

  virtual Solution& applyHeuristic() {
    auto it = solution.getBoats().begin();
    int i = 0;
    while (!stop()) {
      Solution current(solution);
      Boat& boat = *it;
      i++;
      //current.moveHost(-1, -1, boat.getNumber());
      current.moveSwap();
      if (current.getCost() <= solution.getCost()) {
	solution = current;
      }
      it++;
      b_stop = it == solution.getBoats().end();
    }
    cout << "loopcount: " << i << endl;
    return solution;
  }

  virtual bool stop() {
    return b_stop;
  }
};

#endif
