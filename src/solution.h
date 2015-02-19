#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include "boat.h"

class Solution {
 private:
  int number_of_periods;
  int cost;
  std::vector<Boat>& boats;
  /**
   * Which crew are hosting for this period.
   */
  std::vector<std::set<int> > host_set;
  /**
   * crew ==> boat currently on
   */
  std::vector<std::map<int, int> > crew_map;
  /**
   * boat ==> current occupation
   */
  std::vector<std::map<int, int> > occupation_map;
  /**
   * crew ==> other crew met so far
   */
  std::vector<std::map<int, std::list<int> > > meeting_map;

 protected:
  std::list<int>::iterator m_map_find(int period, int target, int toFind);

 public:
  Solution(int number_of_time_periods, std::vector<Boat>& boats);

  int calculateCost();
  int calculateCostPeriod(int period, bool includeC2 = false);
  /**
   * Constraint #1:
   *   Each guest crew moves to a different host at each time period.
   */
  int calculateConstraint1(int period, int crew_num);
  /**
   * Constraint #2:
   *   Two crews meet at most once.
   */
  int calculateConstraint2(int period, int crew_num);
  /**
   * Constraint #3:
   *   The capacities of the host boats must be respected.
   */
  int calculateConstraint3(int period, int host_num);
  //  int updateCost();
  int getConflict(int targetPeriod);

  /**
   * Moves a crew to a different host. Setting the values to -1 picks one at random.
   */
  void moveHost(int targetPeriod = -1, int targetCrew = -1, int targetHost = -1);
  void moveSwap();

  int getNumber_of_periods() const;
  int getCost() const;
  std::vector<Boat>& getBoats() const;
  std::vector<std::set<int> >& getHost_set();
  std::vector<std::map<int, int> >& getCrew_map();
  std::vector<std::map<int, int> >& getOccupation_map();
  std::vector<std::map<int, std::list<int> > >& getMeeting_map();

  Solution& operator=(const Solution&);
};

std::ostream& operator<<(std::ostream& out, Solution& right);

#endif
