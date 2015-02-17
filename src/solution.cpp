#include "solution.h"

using namespace std;

Solution::Solution(int number_of_periods, std::vector<Boat>& boats) :
  number_of_periods(number_of_periods), boats(boats) {
  for (int period = 0; period < number_of_periods; period++) {
    map<int, int> c_map;
    map<int, int> o_map;
    map<int, set<int> > m_map;
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
      m_map[current_num].emplace(host_num);
      m_map[host_num].emplace(current_num);
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
  for (int period = 0; period < number_of_periods; period++) {
    
  }
  this->cost = cost;
  return cost;
}

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

std::vector<std::map<int, std::set<int> > >& Solution::getMeeting_map() {
  return meeting_map;
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
