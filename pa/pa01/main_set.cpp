// Feb 14: This file should implement the game using the std::set container
// class Do not include card_list.h in this file
#include "card.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

int main(int argv, char **argc) {
  if (argv < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> alice_hand;
  set<Card> bob_hand;

  stringstream str;
  char suit;
  string val;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    str = stringstream(line);
    str >> suit;
    str >> val;
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    str = stringstream(line);
    str >> suit;
    str >> val;
  }
  cardFile2.close();

  return 0;
}
