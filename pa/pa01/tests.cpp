#include "card.h"
#include "game_set.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  stringstream output;
  auto cards = read_cards("../a0.txt", "../b0.txt");
  run_game(cards.first, cards.second, output);
  fstream correct = fstream("../o_0.txt");
  if (!correct.is_open()) {
    cout << "wtf";
    throw;
  }
  string next_simulated;
  string next_correct;
  while (getline(output, next_simulated) && !output.eof() &&
         getline(correct, next_correct) && !correct.eof()) {
    assert(next_correct == next_simulated);
  }
}
