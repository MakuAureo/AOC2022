#include <iostream>
#include <fstream>
#include <string>

enum MOVE { ROCK, PAPER, SCISSORS };

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string string;
  int player1, player2;
  int score = 0;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);
  
  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);
    
    //Get player1's move and match number
    char p1 = string.at(0);
    char p2 = string.at(2);
    switch (p1) {
      case 'A':
        player1 = ROCK;
        break;
      case 'B':
        player1 = PAPER;
        break;
      case 'C':
        player1 = SCISSORS;
        break;
    }
    int match;
    switch (p2) {
      case 'X':
        match = 2;
        break;
      case 'Y':
        match = 0;
        break;
      case 'Z':
        match = 1;
        break;
    }

    //Inverting the (mod3) algorithm we can easily get player2's move
    player2 = (match + player1)%3;

    //0 = Draw, 1 = player2 wins, 2 = player2 loses
    switch (match) {
      case 0:
        score += player2 + 1 + 3;
        break;
      case 1:
        score += player2 + 1 + 6;
        break;
      case 2:
        score += player2 + 1;
        break;
    }
  }

  //Output score
  std::cout << score << std::endl;

  return 0;
}
