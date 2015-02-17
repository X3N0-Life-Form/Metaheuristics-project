#include "boat.h"


Boat::Boat() : number(1), capacity(1), crew_size(1)
{}

Boat::Boat(int number, int capacity, int crew_size) :
  number(number), capacity(capacity), crew_size(crew_size)
{}
