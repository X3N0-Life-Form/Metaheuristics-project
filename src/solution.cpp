#include "solution.h"

#include <algorithm>

using namespace std;

list<int>::iterator Solution::m_map_find(int period, int target, int toFind) {
  list<int>::iterator it;
  for (it = meeting_map[period][target].begin();
       it != meeting_map[period][target].end(); it++) {
    if (*it == toFind) {
      return it;
    }
  }
  return it;
}

//TODO: add some randomness
Solution::Solution(int number_of_periods, std::vector<Boat>& boats) :
  number_of_periods(number_of_periods), boats(boats) {
  for (int period = 0; period < number_of_periods; period++) {
    map<int, int> c_map;
    map<int, int> o_map;
    map<int, list<int> > m_map;
    set<int> h_set;
    set<int> out_set; // you can't be hosted by someone that's out
    // some of the crews have already met
    if (period > 0) {
      m_map = meeting_map[period - 1];
    }
    //TODO: a lot of these sub-routines can probably be extracted
    // for search purposes
    for (Boat current_crew : boats) {
      int current_num = current_crew.getNumber();
      // no need to go anywhere if we are already hosting
      if (h_set.find(current_num) != h_set.end()) {
	continue;
      } else {
	out_set.emplace(current_num);
      }
      // position this crew
      int host_num = (rand() % boats.size()) + 1;
      // preferably someplace that's not deserted
      while (out_set.find(host_num) != out_set.end())
	host_num = (rand() % boats.size()) + 1;
      c_map.emplace(current_num, host_num);
      // update host set
      h_set.emplace(host_num);
      // update capacity
      int capacity = current_crew.getCrew_size();
      if (o_map[host_num]) {
	o_map[host_num] += capacity;
      } else {
	o_map[host_num] = capacity;
      }
      // these two crew have met each other
      m_map[current_num].push_back(host_num);
      m_map[host_num].push_back(current_num);
    }
    crew_map.push_back(c_map);
    occupation_map.push_back(o_map);
    meeting_map.push_back(m_map);
    host_set.push_back(h_set);
  }
  calculateCost();
}

int Solution::calculateCost() {
  int cost = 0;
  // C2
  // Note: in theory, we only need to calculate it for the last period.
  for (Boat crew : boats) {
    cost += calculateConstraint2(number_of_periods - 1, crew.getNumber());
  }

  // C1 + C3
  for (int period = 0; period < number_of_periods; period++) {
    cost += calculateCostPeriod(period);
  }
  this->cost = cost;
  return cost;
}

int Solution::calculateCostPeriod(int period, bool includeC2) {
  int cost = 0;
  // Constraint #1:
  if (period > 0) {
    for (int crew_num = 1; crew_num <= (int) boats.size(); crew_num++) {
      cost += calculateConstraint1(period, crew_num);
    }
  }

  // Constraint #3 + #2:
  for (int host_num = 1; host_num <= (int) boats.size(); host_num++) {
    if (host_set[period].find(host_num) != host_set[period].end()) {
      cost += calculateConstraint3(period, host_num);
    }

    if (includeC2) {
      cost += calculateConstraint2(period, host_num);
    }
  }
  return cost;
}


int Solution::calculateConstraint1(int period, int crew_num) {
  if (period == 0) return 0;
  if (crew_map[period][crew_num] != crew_map[period - 1][crew_num]) {
    return 1;
  } else {
    return 0;
  }
}

int Solution::calculateConstraint2(int period, int crew_num) {
  list<int>& crew_met = meeting_map[period][crew_num];
  int cost = 0;
  for (int i = 1; i <= (int) boats.size(); i++) {
    int c = count(crew_met.begin(), crew_met.end(), i);
    if (c > 1) {
	cost += c - 1;
    }
  }
  return cost;
}

int Solution::calculateConstraint3(int period, int host_num) {
  if (occupation_map[period][host_num] > boats[host_num - 1].getCapacity()) {
    return 1;
  } else {
    return 0;
  }
}

int Solution::getMostConflicted(int targetPeriod) {
  int mostConflicted = 1;
  int mostConflicts = 0;
  //cout << "finding conflicts in period " << targetPeriod <<endl;
  for (int crew_num = 1; crew_num <= (int) boats.size(); crew_num++) {
    int conflicts = calculateConstraint1(targetPeriod, crew_num);
    conflicts += calculateConstraint2(targetPeriod, crew_num);
    conflicts += calculateConstraint3(targetPeriod, crew_num);
    if (conflicts > mostConflicts) {
      mostConflicted = crew_num;
      mostConflicts = conflicts;
      //cout << crew_num << " has " << conflicts << " conflicts" << endl;
    }
  }
  return mostConflicted;
}

void Solution::moveHost(int targetPeriod, int targetCrew, int targetHost) {
  if (targetPeriod == -1) targetPeriod = rand() % number_of_periods;
  if (targetCrew == -1) targetCrew = (rand() % boats.size()) + 1;
  if (targetHost == -1) {
    set<int>& h_set = host_set[targetPeriod];
    targetHost = (rand() % boats.size()) + 1;
    while (h_set.find(targetHost) == h_set.end())
      targetHost = (rand() % boats.size()) + 1;
  }
  //cout << "[moveHost] " << targetPeriod << ": " 
  //     <<  targetCrew << " ==> " << targetHost << endl;
  int prevHost = crew_map[targetPeriod][targetCrew];
  crew_map[targetPeriod][targetCrew] = targetHost;
  occupation_map[targetPeriod][prevHost]   -= boats[targetCrew - 1].getCrew_size();
  occupation_map[targetPeriod][targetHost] += boats[targetCrew - 1].getCrew_size();
  // update the meeting map
  for (int i = targetPeriod; i < number_of_periods; i++) {
    // remove them from each other's meeting map
    for (list<int>::iterator it = meeting_map[i][prevHost].begin();
	 it != meeting_map[i][prevHost].end();
	 it++) {
      if (*it == targetCrew) {
	meeting_map[i][prevHost].erase(it);
	break;
      }
    }
    for (list<int>::iterator it = meeting_map[i][targetCrew].begin();
	 it != meeting_map[i][targetCrew].end();
	 it++) {
      if (*it == prevHost) {
	meeting_map[i][targetCrew].erase(it);
	break;
      }
    }
    // add the new meeting to the meeting map
    meeting_map[i][targetHost].push_back(targetCrew);
    meeting_map[i][targetCrew].push_back(targetHost);
  }
  
  // recalculate cost
  calculateCost();//TODO: replace this with updateCost() when it's implemented
}

void Solution::moveSwap(int targetPeriod, int target1, int target2) {
  int t1Host = crew_map[targetPeriod][target1];
  int t2Host = crew_map[targetPeriod][target2];
  crew_map[targetPeriod][target1] = crew_map[targetPeriod][target2];
  crew_map[targetPeriod][target2] = t1Host;

  occupation_map[targetPeriod][t1Host] -= boats[target1 - 1].getCrew_size();
  occupation_map[targetPeriod][t1Host] += boats[target2 - 1].getCrew_size();
  occupation_map[targetPeriod][t2Host] -= boats[target2 - 1].getCrew_size();
  occupation_map[targetPeriod][t2Host] += boats[target1 - 1].getCrew_size();

  /*/
  cout << "targets are " << target1 << " and " << target2 << endl;
  cout << "before\n";
  for (int i : meeting_map[targetPeriod][t1Host]) cout << i << " ";
  cout << " from " << t1Host << endl;
  for (int i : meeting_map[targetPeriod][t2Host]) cout << i << " ";
  cout << " from " << t2Host << endl;
  for (int i : meeting_map[targetPeriod][target1]) cout << i << " ";
  cout << " from " << target1 << endl;
  for (int i : meeting_map[targetPeriod][target2]) cout << i << " ";
  cout << " from " << target2 << endl;
  /*/
  for (int i = targetPeriod; i < number_of_periods; i++) {
    // Remove the old things
    list<int>::iterator it = m_map_find(i, t1Host, target1);
    if (it != meeting_map[i][t1Host].end()) meeting_map[i][t1Host].erase(it);
    it = m_map_find(i, target1, t1Host);
    if (it != meeting_map[i][target1].end()) meeting_map[i][target1].erase(it);
    it = m_map_find(i, t2Host, target2);
    if (it != meeting_map[i][t2Host].end()) meeting_map[i][t2Host].erase(it);
    it = m_map_find(i, target2, t2Host);
    if (it != meeting_map[i][target2].end()) meeting_map[i][target2].erase(it);
    // Add the new things
    meeting_map[i][t1Host].push_back(target2);
    meeting_map[i][target2].push_back(t1Host);
    meeting_map[i][t2Host].push_back(target1);
    meeting_map[i][target1].push_back(t2Host);
  }
  /*/
  cout << "after\n";
  for (int i : meeting_map[targetPeriod][t1Host]) cout << i << " ";
  cout << " from " << t1Host << endl;
  for (int i : meeting_map[targetPeriod][t2Host]) cout << i << " ";
  cout << " from " << t2Host << endl;
  for (int i : meeting_map[targetPeriod][target1]) cout << i << " ";
  cout << " from " << target1 << endl;
  for (int i : meeting_map[targetPeriod][target2]) cout << i << " ";
  cout << " from " << target2 << endl;
  /*/

  calculateCost();
}



/////////////////////////
/// Getters / Setters ///
/////////////////////////

int Solution::getNumber_of_periods() const {
  return number_of_periods;
}

int Solution::getCost() const {
  return cost;
}

vector<Boat>& Solution::getBoats() const {
  return boats;
}

std::vector<std::set<int> >& Solution::getHost_set() {
  return host_set;
}

std::vector<std::map<int, int> >& Solution::getCrew_map() {
  return crew_map;
}

std::vector<std::map<int, int> >& Solution::getOccupation_map() {
  return occupation_map;
}

std::vector<std::map<int, std::list<int> > >& Solution::getMeeting_map() {
  return meeting_map;
}

Solution& Solution::operator=(const Solution& other) {
  number_of_periods = other.number_of_periods;
  cost = other.cost;
  boats = other.boats;
  host_set = other.host_set;
  crew_map = other.crew_map;
  occupation_map = other.occupation_map;
  meeting_map = other.meeting_map;
  return *this;
}


ostream& operator<<(ostream& out, Solution& right) {
  out << "Solution:" << endl;
  for (int i = 0; i < right.getNumber_of_periods(); i++) {
    out << "Period #" << i << ":\n";
    out << "\tcrew positions\toccupation/capacity\n";
    for (unsigned int j = 1; j <= right.getBoats().size(); j++) {
      int host_num = right.getCrew_map()[i][j];
      if (host_num != 0) {
	out << "\t" << j << " ==> " << host_num;
	out << " \t" << right.getOccupation_map()[i][host_num] << "/" << right.getBoats()[host_num].getCapacity();
      } else {
	out << "\t" << j << " ==> host";
      }
      out << endl;
    }
  }
  out << "cost = " << right.getCost();
  return out;
}
