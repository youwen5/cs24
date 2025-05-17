// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's
// hand

#pragma once

#include "card.h"

class CardList {
public:
  class Node {
  public:
    Card val;
    Node *left;
    Node *right;
    Node *parent;
    Node(const Card &v)
        : val(v), left(nullptr), right(nullptr), parent(nullptr) {};
  };
  CardList() : root(nullptr) {};
  bool insert(Card &);
  bool contains(Card &) const;
  bool remove(Card &);
  void printDeck() const;
  Node *getSuccessorNode();
  Node *getPredecessorNode();

private:
  bool insert(Card &, Node *);
  Node *root;
  void printDeck(Node *) const;
  bool contains(Card &, Node *) const;
};
