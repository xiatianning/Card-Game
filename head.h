#ifndef _HEAD_H
#define _HEAD_H
#include <vector>
#include <memory>
#include <string>

class Card;
class Joker;

class Head {
  int number;
  std::vector<std::shared_ptr<Card>> cards;

 public:
  Head(int number, std::shared_ptr<Card> firstCard);
  int getNum() const;          // Returns the number of the head
  std::size_t getSize() const; // Returns the total number of cards in the head
  std::vector<std::shared_ptr<Card>> getCards(); 
  // Removes and returns all the cards in the head
  std::string getTop() const; 
  // Returns the string representing the top card of the head
  bool checkAction(std::shared_ptr<Card> c) const; 
  // Checks whether c can be placed on the head
  bool addCard(std::shared_ptr<Card> c); 
  // Places c on the head and returns whether this action ends the player's turn
};

#endif
