#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "boat.h"

#define LINE_SIZE 1024

void parse(std::string file_path, std::vector<Boat>& vect);
std::vector<std::string> tokenize(std::string toSplit, std::string token);

#endif
