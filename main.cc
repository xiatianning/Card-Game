#include <iostream>
#include <string>
#include <stdexcept>
#include "game.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

int main(int argc, char * argv[]) {
  unsigned int seed = 1;
  bool hasSeed = false;
  bool testMode = false;
  bool bonusMode = false;
  for (int i = 1; i < argc; ++i) {
    string s = string{argv[i]};
    if (s == "-testing") {
      testMode = true;
    } else if (s == "-enablebonus") {
      bonusMode = true;
    } else {
      try {
        unsigned int temp = stoi(s);
        seed = temp;
        hasSeed = true;
      } catch (...) {
        cout << "Invalid Command Line Argument!" << endl;
      } 
    }
  }
  int n;
  cout << "How many players?" << endl;
  while (true) {
    if (!(cin >> n)) {
      cout << "Invalid input! Input again?" << endl;
      if (cin.eof()) {
        return 0;
      } else {
        cin.clear();
        cin.ignore();
      }
    } else {
      if (n > 1) {
        break;
      } else {
        cout << "Invalid input! Input again?" << endl;
      }
    }
  }
  Game g{n, testMode, bonusMode, hasSeed, seed};
  g.playGame();
}
