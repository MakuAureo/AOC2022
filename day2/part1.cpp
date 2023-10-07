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
    
    //Get both players' moves
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
    switch (p2) {
      case 'X':
        player2 = ROCK;
        break;
      case 'Y':
        player2 = PAPER;
        break;
      case 'Z':
        player2 = SCISSORS;
        break;
    }

    //Using subtraction and the modulos operator (note that x%n for negative x does not give
    //a positive value so we need to add 3 after the operation) we can create an order-dependent 
    //match number that ranges from 0 to 2
    int match = (player2 - player1)%3;
    if (match < 0) match += 3;

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
