// card.h
// Author: Youwen Wu
// All class declarations related to defining a single card go here

#pragma once
#include <string>

enum Suit { Clubs, Diamonds, Spades, Hearts };

class Card {
public:
  Card();
  // Passing invalid data to this constructor is undefined behavior.
  Card(char, std::string);
  bool operator<(const Card &) const;
  bool operator>(const Card &) const;
  bool operator==(const Card &) const;
  bool operator!=(const Card &) const;
  bool operator<=(const Card &) const;
  bool operator>=(const Card &) const;
  Suit get_suit() const { return suit; }
  int get_val() const { return val; }

private:
  Suit suit;
  // between 1 (ace) - 13 (11,12,13 are JQK)
  int val;
  // obtain an integer representation of the order of the suits (0-3 inclusive)
};
