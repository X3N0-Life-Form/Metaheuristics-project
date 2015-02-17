#include "utils.h"

using namespace std;

vector<string> tokenize(string toSplit, string token) {
  unsigned int pos;
  vector<string> result;
  while ((pos = toSplit.find(token)) != string::npos) {
    string nuString = toSplit.substr(0, pos);
    if (!nuString.empty()) {
      result.push_back(nuString);
    }
    toSplit = toSplit.substr(pos + 1);
  }
  result.push_back(toSplit);
  return result;
}

void parse(string file_path, vector<Boat>& vect) {
  cout << "Parsing file " << file_path << endl;
  ifstream file_stream(file_path);
  bool data_reached = false;
  while (file_stream.is_open() && !file_stream.eof()) {
    char line[256];
    file_stream.getline(line, 256, '\n');
    if (data_reached) {
      
    } else if (string(line) == string("------------|---------|----------")) {
      data_reached = true;
    }
  }
}
