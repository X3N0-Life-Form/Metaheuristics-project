#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include "boat.h"

void parse(std::string file_path, std::vector<Boat>& vect);
std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif
