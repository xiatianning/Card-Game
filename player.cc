#include "player.h"
#include "card.h"
#include "joker.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <random>
#include <chrono>
using std::vector;
using std::shared_ptr;
using std::size_t;

Player::Player(bool hasSeed, unsigned int seed)
  : hasSeed{hasSeed}, seed{seed} {}

size_t Player::getDrawSize() const {
  return draw.size();
}

size_t Player::getDiscardSize() const {
  return discard.size();
}

bool Player::hasReserve() const {
  if (reserve.size() > 0) {
    return true;
  } else {
    return false;
  }
}

void Player::addDraw(shared_ptr<Card> c) {
  draw.push_back(c);
}

void Player::addDiscard(shared_ptr<Card> c) {
  discard.push_back(c);
}

void Player::addReserve(shared_ptr<Card> c) {
  reserve.push_back(c);
}

shared_ptr<Card> Player::swapReserve(shared_ptr<Card> c) {
  shared_ptr<Card> reserveCard = reserve[0];
  reserve[0] = c;
  return reserveCard;
}

shared_ptr<Card> Player::drawCard() {
  shared_ptr<Card> c;
  if (draw.size() == 0) {
    if (!hasSeed) {
      seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    std::default_random_engine rng{seed};
    shuffle(discard.begin(), discard.end(), rng);
    for (auto cardDiscarded : discard) {
      draw.push_back(cardDiscarded);
    }
    discard.clear();
  }
  c = draw[draw.size() - 1];
  draw.pop_back();
  return c;
}

void Player::returnReserve() {
  if (reserve.size() > 0) {
    shared_ptr<Card> c = reserve[0];
    draw.push_back(c);
    reserve.pop_back();
  }
}
