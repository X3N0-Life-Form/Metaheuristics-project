#ifndef BOAT_H
#define BOAT_H

class Boat {
 private:
  int number;
  int capacity;
  int crew_size;
 public:
  Boat();
  Boat(int, int, int);

  int getNumber();
  /**
   * = number - 1; useful to know the boat's position in the vector.
   */
  int getId();
  int getCapacity();
  int getCrew_size();
};

#endif
