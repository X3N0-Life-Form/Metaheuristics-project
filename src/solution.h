#ifndef SOLUTION_H
#define SOLUTION_H

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "boat.h"

class Solution {
 private:
  int number_of_periods;
  int cost;
  std::vector<Boat>& boats;
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
  std::vector<std::map<int, std::set<int> > > meeting_map;
 public:
  Solution(int number_of_time_periods, std::vector<Boat>& boats);

  int calculateCost();

  int getNumber_of_periods() const;
  int getCost() const;
  std::vector<Boat>& getBoats() const;
  std::vector<std::set<int> >& getHost_set();
  std::vector<std::map<int, int> >& getCrew_map();
  std::vector<std::map<int, int> >& getOccupation_map();
  std::vector<std::map<int, std::set<int> > >& getMeeting_map();
};

std::ostream& operator<<(std::ostream& out, Solution& right);

#endif
