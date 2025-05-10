// card.h
// Author: Youwen Wu
// All class declarations related to defining a single card go here

#pragma once
#include <ostream>
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
  char get_suit_as_char() const;
  std::string get_val_as_str() const;
  friend std::ostream &operator<<(std::ostream &, const Card &);

private:
  Suit suit;
  // between 1 (ace) - 13 (11,12,13 are JQK)
  int val;
};
