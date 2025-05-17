#include "card.h"
#include "card_list.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

pair<CardList, CardList> read_cards_to_cardlist(string file1, string file2) {
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

pair<set<Card>, set<Card>> read_cards_to_set(string file1, string file2) {
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

void run_game_bst(CardList alice_hand, CardList bob_hand, ostream &os) {
  bool keep_playing = true;

  while (keep_playing) {
    keep_playing = false;
    for (auto card : alice_hand) {
      if (bob_hand.remove(card)) {
        os << "Alice picked matching card " << card << endl;
        alice_hand.remove(card);
        keep_playing = true;
        break;
      }
    }
    for (auto rit = bob_hand.rbegin(); rit != bob_hand.rend(); rit++) {
      if (alice_hand.remove(*rit)) {
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

void run_game_set(set<Card> alice_hand, set<Card> bob_hand, ostream &os) {
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

void test_game_set(int num) {
  stringstream output;
  auto cards = read_cards_to_set("./a" + to_string(num) + ".txt",
                                 "./b" + to_string(num) + ".txt");
  run_game_set(cards.first, cards.second, output);
  fstream correct = fstream("./o_" + to_string(num) + ".txt");
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

void test_game_bst(int num) {
  stringstream output;
  auto cards = read_cards_to_cardlist("./a" + to_string(num) + ".txt",
                                      "./b" + to_string(num) + ".txt");
  run_game_bst(cards.first, cards.second, output);
  fstream correct = fstream("./o_" + to_string(num) + ".txt");
  if (!correct.is_open()) {
    cout << "wtf";
    throw;
  }
  string next_simulated;
  string next_correct;
  while (getline(output, next_simulated) && !output.eof() &&
         getline(correct, next_correct) && !correct.eof()) {

    if (next_correct != next_simulated) {
      cout << "While reading test " << num
           << ", I found these differing lines: " << endl
           << next_correct << endl
           << next_simulated << endl;
    };
    assert(next_correct == next_simulated);
  }
}

void test_bst() {
  // comparison operators
  {
    Card c1('c', "5"), c2('c', "7"), c3('d', "2"), c4('h', "k");
    assert(c1 < c2);
    assert(c1 < c3);
    assert(c4 > c3);
    assert(c2 >= c1);
    assert(c3 != c1);
    assert(!(c1 > c2));
  }

  // empty list behaviour
  {
    CardList l;
    Card c('s', "a");
    assert(!l.contains(c));
    assert(!l.remove(c));
  }

  // insert & contains
  {
    CardList l;
    Card c1('h', "10"), c2('c', "3"), c3('s', "q");
    assert(l.insert(c1));
    assert(l.insert(c2));
    assert(l.insert(c3));
    assert(l.contains(c1));
    assert(l.contains(c2));
    assert(l.contains(c3));
  }

  // duplicate insert rejection
  {
    CardList l;
    Card c('d', "9");
    assert(l.insert(c));
    assert(!l.insert(c));
  }

  // remove leaf
  {
    CardList l;
    Card c1('c', "2"), c2('c', "1"); // c2 becomes left leaf
    l.insert(c1);
    l.insert(c2);
    assert(l.remove(c2));
    assert(!l.contains(c2));
    assert(l.contains(c1));
  }

  // remove node with one child
  {
    CardList l;
    Card root('s', "8"), rightChild('s', "9");
    l.insert(root);
    l.insert(rightChild);
    assert(l.remove(root));
    assert(!l.contains(root));
    assert(l.contains(rightChild));
  }

  // remove node with two children
  {
    CardList l;
    Card r('d', "8"), lft('d', "6"), rgt('d', "10");
    l.insert(r);
    l.insert(lft);
    l.insert(rgt);
    assert(l.remove(r));
    assert(!l.contains(r));
    assert(l.contains(lft) && l.contains(rgt));
  }

  // stress test with full deck
  {
    CardList l;
    std::vector<Card> deck;
    const std::vector<char> suits = {'c', 'd', 's', 'h'};
    const std::vector<std::string> vals = {"a", "2", "3",  "4", "5", "6", "7",
                                           "8", "9", "10", "j", "q", "k"};
    for (char s : suits)
      for (const auto &v : vals)
        deck.emplace_back(s, v);

    std::mt19937 rng(42);
    std::shuffle(deck.begin(), deck.end(), rng);

    for (auto &c : deck)
      assert(l.insert(c));
    for (auto &c : deck)
      assert(l.contains(c));

    std::shuffle(deck.begin(), deck.end(), rng);
    for (auto &c : deck)
      assert(l.remove(c));
    for (auto &c : deck)
      assert(!l.contains(c));
  }
}

int main() {
  // test_bst();
  for (int i = 1; i <= 3; i++) {
    test_game_set(i);
  }
  for (int i = 1; i <= 3; i++) {
    test_game_bst(i);
  }
}
