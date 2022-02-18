#ifndef _CARD_H
#define _CARD_H
#include <string>

class Card {
  int value;
  char suit;

 protected:
  std::string convertValue() const; 
  // Returns the string representing the card value
  
 public:
  Card(int value, char suit);
  int getValue() const;     // Returns the value of the card 
  void setValue(int value); // Sets the value of the card
  char getSuit() const;     // Returns the suit of the card
  void setSuit(char suit);  // Sets the suit of the card
  virtual void announceHeadValue(); 
  // Announces the value of the card when it is selected to be a head
  virtual bool announceDrawValue();
  // Announces the value of the card when it is played
  //   and returns whether it is done successfully
  virtual std::string nameHand() const;
  // Returns the string representing the card when it is in the player's hand
  virtual std::string namePlayed() const;
  // Returns the string representing the card when it is placed on a head
  virtual ~Card();
};

#endif
