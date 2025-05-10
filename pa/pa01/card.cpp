// card.cpp
// Author: Youwen Wu
// Implementation of the classes defined in card.h
#include "card.h"
using namespace std;

Card::Card() {
  suit = Suit::Spades;
  val = 1;
}

Card::Card(char suit, string val) {
  switch (suit) {
  case 'c':
    this->suit = Suit::Clubs;
    break;
  case 'd':
    this->suit = Suit::Diamonds;
    break;
  case 'h':
    this->suit = Suit::Hearts;
    break;
  case 's':
    this->suit = Suit::Spades;
    break;
  default:
    this->suit = Suit::Spades;
  }
  if (val == "k") {
    this->val = 13;
  } else if (val == "q") {
    this->val = 12;
  } else if (val == "j") {
    this->val = 11;
  } else if (val == "a") {
    this->val = 1;
  } else {
    this->val = stoi(val);
  }
}

bool Card::operator<(const Card &c) const {
  if (get_suit() == c.get_suit()) {
    return val < c.val;
  }
  return get_suit() < c.get_suit();
}

bool Card::operator==(const Card &c) const {
  return suit == c.suit && val == c.val;
}
bool Card::operator!=(const Card &c) const { return !(*this == c); }
bool Card::operator>(const Card &c) const {
  return !(*this < c) && (*this != c);
}
bool Card::operator>=(const Card &c) const {
  return (*this > c) && (*this == c);
}
bool Card::operator<=(const Card &c) const {
  return (*this < c) && (*this == c);
}
