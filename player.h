#ifndef _PLAYER_H
#define _PLAYER_H
#include <vector>
#include <memory>

class Card;
class Joker;

class Player {
  std::vector<std::shared_ptr<Card>> draw;
  std::vector<std::shared_ptr<Card>> discard;
  std::vector<std::shared_ptr<Card>> reserve;
  bool hasSeed;
  unsigned int seed;

 public:
  Player(bool hasSeed, unsigned int seed);
  std::size_t getDrawSize() const;     // Returns the number of cards in draw pile
  std::size_t getDiscardSize() const;  // Returns the number of cards in discard pile 
  bool hasReserve() const;             // Returns whether there is reserve
  void addDraw(std::shared_ptr<Card> c);    // Adds card to draw pile
  void addDiscard(std::shared_ptr<Card> c); // Adds card to discard pile
  void addReserve(std::shared_ptr<Card> c); // Places card into reserve
  std::shared_ptr<Card> swapReserve(std::shared_ptr<Card> c); 
  // Swaps card with the reserve card
  std::shared_ptr<Card> drawCard(); // Draws a card
  void returnReserve();             // Returns the reserve to the draw pile
};

#endif
