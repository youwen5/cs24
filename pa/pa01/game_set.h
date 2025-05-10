// Common code for running the set version of the game, to be shared in
// `main_set.cpp` and `tests.cpp`
#pragma once
#include "card.h"
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

pair<set<Card>, set<Card>> read_cards(string file1, string file2);

void run_game(set<Card> alice_hand, set<Card> bob_hand, ostream &os);
