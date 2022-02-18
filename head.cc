#include "head.h"
#include "card.h"
#include "joker.h"
#include <vector>
#include <memory>
#include <string>
using std::size_t;
using std::vector;
using std::shared_ptr;
using std::string;

Head::Head(int number, shared_ptr<Card> firstCard) : number{number} {
  cards.push_back(firstCard);
}

int Head::getNum() const {
  return number;
}

size_t Head::getSize() const {
  return cards.size();
}

vector<shared_ptr<Card>> Head::getCards() {
  vector<shared_ptr<Card>> temp = cards;
  cards.clear();
  return temp;
}

string Head::getTop() const {
  return (cards[cards.size() - 1])->namePlayed();
}

bool Head::checkAction(shared_ptr<Card> c) const {
  if ((c->getValue()) <= ((cards[cards.size() - 1])->getValue())) {
    return true;
  } else if ((cards[cards.size() - 1])->getValue() == 1) {
    return true;
  } else {
    return false;
  }
}

bool Head::addCard(shared_ptr<Card> c) {
  bool endTurn = false;
  if ((c->getValue()) == ((cards[cards.size() - 1])->getValue())) {
    endTurn = true;
  }
  cards.push_back(c);
  return endTurn;
}
