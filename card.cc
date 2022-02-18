#include "card.h"
#include <string>
using std::string;
using std::to_string;

string Card::convertValue() const {
  string v;
  if (value == 1) {
    v += "A";
  } else if (value == 11) {
    v += "J";
  } else if (value == 12) {
    v += "Q";
  } else if (value == 13) {
    v += "K";
  } else {
    v += to_string(value);
  }
  return v;
}

Card::Card(int value, char suit) : value{value}, suit{suit} {}

int Card::getValue() const {
  return value;
}

void Card::setValue(int value) {
  this->value = value;
}

char Card::getSuit() const {
  return suit;
}

void Card::setSuit(char suit) {
  this->suit = suit;
}

void Card::announceHeadValue() {}

bool Card::announceDrawValue() {
  return true;
}

string Card::nameHand() const {
  string name = convertValue();
  name += suit;
  return name;
}

string Card::namePlayed() const {
  return nameHand();
}

Card::~Card() {}
