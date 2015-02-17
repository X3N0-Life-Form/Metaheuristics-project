#include "boat.h"


Boat::Boat() : number(1), capacity(1), crew_size(1)
{}

Boat::Boat(int number, int capacity, int crew_size) :
  number(number), capacity(capacity), crew_size(crew_size)
{}

int Boat::getNumber() {
  return number;
}

int Boat::getId() {
  return number - 1;
}

int Boat::getCapacity() {
  return capacity;
}

int Boat::getCrew_size() {
  return crew_size;
}
