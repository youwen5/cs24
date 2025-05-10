// Feb 14: This file should implement the game using the std::set container
// class Do not include card_list.h in this file
#include "card.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

using namespace std;

pair<set<Card>, set<Card>> read_cards(string file1, string file2) {
  ifstream cardFile1(file1);
  ifstream cardFile2(file2);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << file1;
    throw;
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
    alice_hand.insert(Card(suit, val));
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    str = stringstream(line);
    str >> suit;
    str >> val;
    bob_hand.insert(Card(suit, val));
  }
  cardFile2.close();

  return pair<set<Card>, set<Card>>(alice_hand, bob_hand);
}

void run_game(set<Card> alice_hand, set<Card> bob_hand) {
  bool keep_playing = true;

  while (keep_playing) {
    keep_playing = false;
    for (auto card : alice_hand) {
      if (bob_hand.erase(card) > 0) {
        cout << "Alice picked matching card " << card << endl;
        alice_hand.erase(card);
        keep_playing = true;
        break;
      }
    }
    for (auto rit = bob_hand.rbegin(); rit != bob_hand.rend(); rit++) {
      if (alice_hand.erase(*rit) > 0) {
        cout << "Bob picked matching card " << (*rit) << endl;
        bob_hand.erase(*rit);
        keep_playing = true;
        break;
      }
    }
  }

  cout << endl;

  cout << "Alice's cards:" << endl;
  for (auto card : alice_hand) {
    cout << card << endl;
  }

  cout << endl;

  cout << "Bob's cards:" << endl;
  for (auto card : bob_hand) {
    cout << card << endl;
  }
}

int main(int argv, char **argc) {
  if (argv < 3) {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  auto cards = read_cards(argc[1], argc[2]);

  run_game(cards.first, cards.second);

  return 0;
}
