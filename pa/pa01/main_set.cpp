// Feb 14: This file should implement the game using the std::set container
// class Do not include card_list.h in this file
#include "game_set.h"
#include <iostream>

using namespace std;

int main(int argv, char **argc) {
  if (argv < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  auto cards = read_cards(argc[1], argc[2]);

  run_game(cards.first, cards.second, cout);

  return 0;
}
