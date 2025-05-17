// Feb 14: This file should implement the game using a custom implementation of
// a BST (that is based on your implementation from lab02)
#include "card.h"
#include "card_list.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// Do not include set in this file

using namespace std;

void test_insert() {
  CardList c;
  vector<Card> card_vec;
  card_vec.push_back(Card('c', "a"));
  card_vec.push_back(Card('s', "5"));
  card_vec.push_back(Card('h', "3"));

  for (auto i : card_vec) {
    c.insert(i);
  }

  c.printDeck();
}

void test_contains() {
  CardList c;
  vector<Card> card_vec;
  card_vec.push_back(Card('c', "a"));
  card_vec.push_back(Card('s', "5"));
  card_vec.push_back(Card('h', "3"));

  for (auto i : card_vec) {
    c.insert(i);
  }

  Card not_in = Card('h', "4");

  cout << "test contains 1" << endl;
  assert(c.contains(card_vec.at(0)));
  cout << "test contains 2" << endl;
  assert(!c.contains(not_in));
}

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

  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
  }
  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
  }
  cardFile2.close();

  test_insert();
  test_contains();

  return 0;
}
