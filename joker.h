#ifndef _JOKER_H
#define _JOKER_H
#include "card.h"
#include <string>

class Joker : public Card {
 public:
  Joker(int value, char suit);
  void announceHeadValue() override;
  bool announceDrawValue() override;
  std::string nameHand() const override;
  std::string namePlayed() const override;
};

#endif
