// Feb 14: This file should implement the game using a custom implementation of
// a BST (that is based on your implementation from lab02)
#include "card.h"
#include "card_list.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
// Do not include set in this file

using namespace std;

pair<CardList, CardList> read_cards(string file1, string file2) {
  ifstream cardFile1(file1);
  ifstream cardFile2(file2);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << file1;
    throw;
  }

  CardList alice_hand;
  CardList bob_hand;

  stringstream str;
  char suit;
  string val;

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    str = stringstream(line);
    str >> suit;
    str >> val;
    Card to_insert = Card(suit, val);
    alice_hand.insert(to_insert);
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    str = stringstream(line);
    str >> suit;
    str >> val;
    Card to_insert = Card(suit, val);
    bob_hand.insert(to_insert);
  }
  cardFile2.close();

  return pair<CardList, CardList>(alice_hand, bob_hand);
}

void run_game_bst(CardList alice_hand, CardList bob_hand, ostream &os) {
  bool keep_playing = true;

  while (keep_playing) {
    keep_playing = false;
    for (auto card : alice_hand) {
      if (bob_hand.remove(card) > 0) {
        os << "Alice picked matching card " << card << endl;
        alice_hand.remove(card);
        keep_playing = true;
        break;
      }
    }
    for (auto rit = bob_hand.begin(); rit != bob_hand.end(); rit++) {
      if (alice_hand.remove(*rit) > 0) {
        os << "Bob picked matching card " << (*rit) << endl;
        bob_hand.remove(*rit);
        keep_playing = true;
        break;
      }
    }
  }

  os << endl;

  os << "Alice's cards:" << endl;
  for (auto card : alice_hand) {
    os << card << endl;
  }

  os << endl;

  os << "Bob's cards:" << endl;
  for (auto card : bob_hand) {
    os << card << endl;
  }
}

int main(int argv, char **argc) {
  if (argv < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  auto cards = read_cards(argc[1], argc[2]);

  run_game_bst(cards.first, cards.second, cout);

  return 0;
}
