#include "card.h"
#include "card_list.h"
#include "game_set.h"
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

using namespace std;

void test_game_set() {
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
    // assert(!l.remove(c));
    // assert(l.getSuccessorNode() == nullptr);
    // assert(l.getPredecessorNode() == nullptr);
  }

  // insert-contains basic
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
  // {
  //   CardList l;
  //   Card parent('c', "2"), leaf('c', "1");
  //   l.insert(parent);
  //   l.insert(leaf);
  //   assert(l.remove(leaf));
  //   assert(!l.contains(leaf));
  //   assert(l.contains(parent));
  // }

  // remove node with one child
  // {
  //   CardList l;
  //   Card root('s', "8"), child('s', "9");
  //   l.insert(root);
  //   l.insert(child);
  //   assert(l.remove(root));
  //   assert(!l.contains(root));
  //   assert(l.contains(child));
  // }

  // remove node with two children
  // {
  //   CardList l;
  //   Card r('d', "8"), lft('d', "6"), rgt('d', "10");
  //   l.insert(r);
  //   l.insert(lft);
  //   l.insert(rgt);
  //   assert(l.remove(r));
  //   assert(!l.contains(r));
  //   assert(l.contains(lft) && l.contains(rgt));
  // }

  // successor & predecessor on three-node tree
  // {
  //   CardList l;
  //   Card root('c', "5"), left('c', "3"), right('c', "7");
  //   l.insert(root);
  //   l.insert(left);
  //   l.insert(right);
  //   auto *succ = l.getSuccessorNode();
  //   auto *pred = l.getPredecessorNode();
  //   assert(succ && succ->val == right);
  //   assert(pred && pred->val == left);
  // }

  // successor & predecessor on single-node tree
  // {
  //   CardList l;
  //   Card only('d', "9");
  //   l.insert(only);
  //   assert(l.getSuccessorNode() == nullptr);
  //   assert(l.getPredecessorNode() == nullptr);
  // }

  // stress test full deck
  // {
  //   CardList l;
  //   std::vector<Card> deck;
  //   const std::vector<char> suits = {'c', 'd', 's', 'h'};
  //   const std::vector<std::string> vals = {"a", "2", "3",  "4", "5", "6",
  //   "7",
  //                                          "8", "9", "10", "j", "q", "k"};
  //   for (char s : suits)
  //     for (const auto &v : vals)
  //       deck.emplace_back(s, v);
  //
  //   std::mt19937 rng(42);
  //   std::shuffle(deck.begin(), deck.end(), rng);
  //   for (auto &c : deck)
  //     assert(l.insert(c));
  //   for (auto &c : deck)
  //     assert(l.contains(c));
  //
  //   std::shuffle(deck.begin(), deck.end(), rng);
  //   for (auto &c : deck)
  //     assert(l.remove(c));
  //   for (auto &c : deck)
  //     assert(!l.contains(c));
  // }
}

int main() {
  test_bst();
  test_game_set();
}
