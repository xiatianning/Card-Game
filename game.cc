#include "game.h"
#include "player.h"
#include "head.h"
#include "card.h"
#include "joker.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
using std::cin;
using std::cout;
using std::endl;
using std::istringstream;
using std::string;
using std::getline;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::size_t;

bool Game::setCard(shared_ptr<Card> &c) const {
  if (testMode) {
    int v;
    bool valid = false;
    while (!valid) {
      cout << "Card value?" << endl;
      string s;
      cin >> s;
      if (cin.eof()) {
        return false;
      }
      istringstream ss{s};
      int n;
      if (ss >> n) {
        if ((n >= 2) && (n <= 10)) {
          v = n;
          valid = true;
        }
      } else {
        for (size_t i = 0; i < s.size(); ++i) {
          if ((s[i] >= 'a') && (s[i] <= 'z')) {
            s[i]  = s[i] - 'a' + 'A';   // Lowercase is also accepted
          }
        }
        if (s.size() == 1) {
          char value = s[0];
          if (value == 'A') {
            v = 1;
            valid = true;
          } else if (value == 'J') {
            v = 11;
            valid = true;
          } else if (value == 'Q') {
            v = 12;
            valid = true;
          } else if (value == 'K') {
            v = 13;
            valid = true;
          }
        } else if (s.size() == 5) {
          if (s == "JOKER") {
            c = make_shared<Joker>(0, 'J');
            return true;
          }
        }
      }
    }
    char suit;
    while (true) {
      cout << "Suit?" << endl;
      char c;
      cin >> c;
      if (cin.eof()) {
        return false;
      }
      if ((c >= 'a') && (c <= 'z')) {
        c = c - 'a' + 'A';            // Lowercase is also accepted
      }
      if ((c == 'S') || (c == 'H') || (c == 'C') || (c == 'D')) {
        suit = c;
        break;
      }
    }
    c = make_shared<Card>(v, suit);
  }
  return true;
}

void Game::printHeads() const {
  cout << "Heads:" << endl;
  if (!bonusMode) {
    for (auto h : heads) {
      cout << h.getNum() << ": " << h.getTop() << " ";
      cout << "(" << h.getSize() << ")" << endl;
    }
  } else {
    for (auto h : heads) {
      string cardName = h.getTop();
      for (int i = 1; i <= 9; ++i) {
        if ((i == 1) || (i == 9)) {
          cout << " ------- " << endl;
        } else if (i == 2) {
          cout << "|" << cardName;
          for (int j = 7 - cardName.size(); j >= 1; --j) {
            cout << " ";
          }
          cout << "|" << endl;
        } else if (i == 8) {
          cout << "|";
          for (int j = 7 - cardName.size(); j >= 1; --j) {
            cout << " ";
          }
          cout << cardName << "|" << endl;
        } else if (i == 5) {
          cout << "|   ";
          char suit = cardName[cardName.size() - 1];
          if (suit == 'S') {
            cout << "\u2660";
          } else if (suit == 'C') {
            cout << "\u2663";
          } else if (suit == 'H') {
            cout << "\u2665";
          } else if (suit == 'D') {
            cout << "\u2666";
          } else {
            cout << suit;
          }
          cout << "   |";
          cout << " " << h.getNum() << " (" << h.getSize() << ")" << endl;
        } else {
          cout << "|       |" << endl;
        }
      }
    }
  }
  cout << endl;
}

void Game::printPlayers(size_t currentPlayer, size_t remaining) const {
  cout << "Players:" << endl;
  for (size_t i = 0; i < players.size(); ++i) {
    Player p = players[i];
    cout << "Player " << i + 1 << ": ";
    cout << p.getDrawSize() + p.getDiscardSize() << " ";
    cout << "(" << p.getDrawSize() << " draw, ";
    cout << p.getDiscardSize() << " discard)";
    if ((i + 1) == currentPlayer) {
      cout << " + 1 in hand, " << remaining << " remaining, ";
      int reserveCount = 0;
      if (p.hasReserve()) {
        reserveCount = 1;
      }
      cout << reserveCount << " in reserve";
    }
    cout << endl;
  }
  cout << endl;
}

void Game::askMove(size_t playerNum, shared_ptr<Card> c) const {
  cout << "Player " << playerNum << ", you are holding ";
  if (bonusMode && ((c->getValue() == 1) || (c->getValue() == 8))) {
    cout << "an ";
  } else {
    cout << "a ";
  }
  cout << c->nameHand() << ". Your move?" << endl;	
}

void Game::firstMove() {
  shared_ptr<Card> first = players[0].drawCard();
  if (setCard(first)) {
    first->announceHeadValue();
    Head h{1, first};
    heads.push_back(h);
  }
}

Game::Game(int numPlayer, bool testMode, bool bonusMode, bool hasSeed, unsigned int seed) 
  : testMode{testMode}, bonusMode{bonusMode}, hasSeed{hasSeed}, seed{seed} {
  vector<shared_ptr<Card>> cards;
  for (int n = 1; n <= numPlayer; ++n) {
    for (int i = 1; i <= 4; ++i) {
      char suit;
      if (i == 1) {
        suit = 'S';
      } else if (i == 2) {
        suit = 'H';
      } else if (i == 3) {
        suit = 'C';
      } else {
        suit = 'D';
      }
      for (int j = 1; j <= 13; ++j) {
        auto card = make_shared<Card>(j, suit);
        cards.push_back(card);
      }
    }
    for (int k = 1; k <= 2; ++k) {
      auto card = make_shared<Joker>(0, 'J');
      cards.push_back(card);
    }
  }
  if (!hasSeed) {
    seed = std::chrono::system_clock::now().time_since_epoch().count();
  }
  std::default_random_engine rng{seed};
  std::shuffle(cards.begin(), cards.end(), rng);
  int index = 0;
  for (int n = 1; n <= numPlayer; ++n) {
    Player p{hasSeed, seed};
    for (int i = 1; i <= 54; ++i) {
      p.addDraw(cards[index]);
      ++index;
    }
    players.push_back(p);
  }
  firstMove();
}

void Game::playGame() {
  bool win = false;
  size_t playerNum = 2;
  while((!win) && (heads.size() > 0)) {
    if (playerNum > players.size()) {
      playerNum = 1;
    }
    cout << endl;
    printHeads();
    printPlayers();
    cout << "Player " << playerNum << ", it is your turn." << endl;
    string line;
    for (int i = 1; i <= 2; ++i) {
      if (!(getline(cin, line))) {
        return;
      }
    }
    Player &p = players[playerNum - 1];
    shared_ptr<Card> c;
    size_t moveCount = 1;
    bool end = false;
    bool swapped = false;
    while ((moveCount <= heads.size()) && (!end)) {
      if (!swapped) {
        c = p.drawCard();
      }
      cout << endl;
      printHeads();
      printPlayers(playerNum, heads.size() - moveCount);
      int move;
      bool valid = false;
      while (!valid) {
        if (!setCard(c)) {
          return;
        }
        askMove(playerNum, c);
        while (!(cin >> move)) {
          if (cin.eof()) {
            return;
          } else {
            cout << "invalid character!" << endl;
            cin.clear();   // Ignores non-integer inputs.
            cin.ignore();
          }
        }
        if (move == 0) {
          if (p.hasReserve()) {
            if (!swapped) {
              c = p.swapReserve(c);
              valid = true;
              swapped = true;
            }
          } else if (heads.size() > 1){
            p.addReserve(c);
            valid = true;
            ++moveCount;
            swapped = false;
          }
        } else if ((move >= heads[0].getNum()) && 
                   (move <= heads[heads.size() - 1].getNum())) {
          if (!(c->announceDrawValue())) {
            return;
          }
          int firstNum = heads[0].getNum();
          Head &h = heads[move - firstNum];
          if (h.checkAction(c)) {
            end = h.addCard(c);
            valid = true;
            ++moveCount;
            swapped = false;
          } else if (move == heads[0].getNum()) {
            bool cutHead = true;
            if ((!(p.hasReserve())) && (heads.size() > 1)) {
              cutHead = false;
            }
            for (auto n : heads) {
              if (n.checkAction(c)) {
                cutHead = false;
              }
            }
            if (cutHead || bonusMode) {
              p.addDiscard(c);
              p.returnReserve();
              for (auto n : heads[0].getCards()) {
                p.addDiscard(n);
              }
              int headNum = heads[heads.size() - 1].getNum();
              heads.erase(heads.begin());
              for (int i = 1; i <= 2; ++i) {
                shared_ptr<Card> newCard = p.drawCard();
                if (!setCard(newCard)) {
                  return;
                }
                newCard->announceHeadValue();
                Head newHead{headNum + i, newCard};
                heads.push_back(newHead);
              }
              valid = true;
              end = true;
            }
          }
        }
      }
      if ((p.getDrawSize() == 0) && (p.getDiscardSize() == 0) &&
          (!p.hasReserve())) {
        end = true;
        win = true;
        cout << "Player " << playerNum << " wins!" << endl;
      } else if ((p.getDrawSize() == 0) && (p.getDiscardSize() == 0)) {
        end = true;
      }
    }
    p.returnReserve();
    ++playerNum;
  }
}
