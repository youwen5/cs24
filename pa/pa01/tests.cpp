#include "card.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

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

void run_game(set<Card> alice_hand, set<Card> bob_hand, ostream &os) {
  bool keep_playing = true;

  while (keep_playing) {
    keep_playing = false;
    for (auto card : alice_hand) {
      if (bob_hand.erase(card) > 0) {
        os << "Alice picked matching card " << card << endl;
        alice_hand.erase(card);
        keep_playing = true;
        break;
      }
    }
    for (auto rit = bob_hand.rbegin(); rit != bob_hand.rend(); rit++) {
      if (alice_hand.erase(*rit) > 0) {
        os << "Bob picked matching card " << (*rit) << endl;
        bob_hand.erase(*rit);
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

  // run_game(cards.first, cards.second, output);
  // cards = read_cards("../a1.txt", "../b1.txt");
  // run_game(cards.first, cards.second, output);
  // cards = read_cards("../a2.txt", "../b2.txt");
  // run_game(cards.first, cards.second, output);
  // cards = read_cards("../a3.txt", "../b3.txt");
  // run_game(cards.first, cards.second, output);
}
