// intlist.cpp
// Implements class IntList
// Youwen Wu, AND 4/12/25

#include "intlist.h"

#include <iostream>
using namespace std;

// copy constructor
IntList::IntList(const IntList &source) {
  head = tail = nullptr;
  Node *ptr1 = source.head;

  while (ptr1 != nullptr) {
    push_back(ptr1->info);
    ptr1 = ptr1->next;
  }
}

void IntList::clear() {
  Node *ptr = head;
  Node *temp;
  while (ptr != nullptr) {
    temp = ptr->next;
    delete ptr;
    ptr = temp;
  }
  head = tail = nullptr;
}

// destructor deletes all nodes
IntList::~IntList() { clear(); }

// return sum of values in list
int IntList::sum() const {
  Node *ptr = head;
  int sum = 0;
  while (ptr != nullptr) {
    sum += ptr->info;
    ptr = ptr->next;
  }
  return sum;
}

// returns true if value is in the list; false if not
bool IntList::contains(int value) const {
  Node *ptr = head;

  while (ptr != nullptr) {
    if (ptr->info == value) {
      return true;
    }
    ptr = ptr->next;
  }

  return false;
}

// returns maximum value in list, or 0 if empty list
int IntList::max() const {
  if (head == nullptr)
    return 0;

  int max = head->info;
  Node *ptr = head->next;

  while (ptr != nullptr) {
    if (ptr->info > max) {
      max = ptr->info;
    }
    ptr = ptr->next;
  }

  return max; // REPLACE THIS NON-SOLUTION
}

// returns average (arithmetic mean) of all values, or
// 0 if list is empty
double IntList::average() const {
  int ct = count();
  if (ct == 0)
    return 0;
  return static_cast<double>(sum()) / ct;
}

// inserts value as new node at beginning of list
void IntList::push_front(int value) {
  Node *newNode = new Node;
  newNode->info = value;
  newNode->next = head;
  head = newNode;
  if (tail == nullptr) {
    tail = head;
  }
}

// append value at end of list
void IntList::push_back(int value) {
  if (head == nullptr || head == tail) {
    push_front(value);
    return;
  }

  Node *newNode = new Node();
  newNode->info = value;
  newNode->next = nullptr;
  tail->next = newNode;
  tail = newNode;
}

// return count of values
int IntList::count() const {
  int ct = 0;
  Node *ptr = head;
  while (ptr != nullptr) {
    ct++;
    ptr = ptr->next;
  }
  return ct;
}

// Assignment operator should copy the list from the source
// to this list, deleting/replacing any existing nodes
IntList &IntList::operator=(const IntList &source) {
  if (this == &source)
    return *this;

  clear();

  Node *ptr1 = source.head;

  while (ptr1 != nullptr) {
    push_back(ptr1->info);
    ptr1 = ptr1->next;
  }

  return *this;
}

// constructor sets up empty list
IntList::IntList() {
  // IMPLEMENT THIS
  head = tail = nullptr;
}

// DO NOT CHANGE ANYTHING BELOW (READ IT THOUGH)

// print values enclose in [], separated by spaces
void IntList::print() const {
  Node *n = head;
  cout << '[';
  while (n) {
    cout << n->info;
    if (n->next)
      cout << " ";
    n = n->next;
  }
  cout << ']';
}
