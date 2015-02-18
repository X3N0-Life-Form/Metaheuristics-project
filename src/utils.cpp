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
  //cout << "Parsing file " << file_path << endl;
  ifstream file_stream(file_path);
  bool data_reached = false;
  int i = 0;
  while (file_stream.is_open() && !file_stream.eof()) {
    char c_line[LINE_SIZE];
    file_stream.getline(c_line, LINE_SIZE);
    string line(c_line);
    if (data_reached && line.size() > 0) {
      //cout << "\tParsing line #" << i << ": " << line << endl;
      vector<string> items = tokenize(line, string("|"));
      int number = stoi(items[0]);
      int capacity = stoi(items[1]);
      int crew_size = stoi(items[2]);
      vect.push_back(Boat(number, capacity, crew_size));
    } else if (line == string("------------|---------|----------")) {
      data_reached = true;
    }
    i++;
  }
}
