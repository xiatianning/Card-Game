#ifndef _GAME_H
#define _GAME_H
#include "player.h"
#include "head.h"
#include <vector>
#include <memory>

class Card;
class Joker;

class Game {
  std::vector<Player> players;
  std::vector<Head> heads;
  bool testMode;
  bool bonusMode;
  bool hasSeed;
  unsigned int seed;

  bool setCard(std::shared_ptr<Card> &c) const; 
  // Sets the value and suit of c and returns whether it is successfully done
  void printHeads() const;                       // Prints the list of heads
  void printPlayers(std::size_t currentPlayer = 0, std::size_t remaining = 0) const;
  // Prints the list of players
  void askMove(std::size_t playerNum, std::shared_ptr<Card> c) const;
  // Prints the interactive prompt for acking the player's move
  void firstMove();  // Starts a head for the game

 public:
  Game(int numPlayer, bool testMode, bool bonusMode, bool hasSeed, unsigned int seed);
  void playGame();  // Plays the game
};

#endif
