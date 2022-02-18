#include "joker.h"
#include "card.h"
#include <iostream>
#include <sstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::string;

Joker::Joker(int value, char suit) : Card{value, suit} {}

void Joker::announceHeadValue() {
  setValue(2);
}

bool Joker::announceDrawValue() {
  bool valid = false;
  while (!valid) {
    cout << "Joker value?" << endl;
    string s;
    cin >> s;
    if (cin.eof()) {
      return false;
    }
    istringstream ss{s};
    int n;
    if (ss >> n) {
      if ((n >= 2) && (n <= 10)) {
        setValue(n);
        valid = true;
      }
    } else if (s.length() == 1) {
      char value = s[0];
      if ((value >= 'a') && (value <= 'z')) {
        value = value - 'a' + 'A';            // Lowercase is also accepted
      }
      if (value == 'A') {
        setValue(1);
        valid = true;
      } else if (value == 'J') {
        setValue(11);
        valid = true;
      } else if (value == 'Q') {
        setValue(12);
        valid = true;
      } else if (value == 'K') {
        setValue(13);
        valid = true;
      }
    }
  }
  return true;
}

string Joker::nameHand() const {
  return "Joker";
}

string Joker::namePlayed() const {
  string name = convertValue();
  name += getSuit();
  return name;
}

