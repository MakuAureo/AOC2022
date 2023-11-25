#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

enum DIREC {
  RIGHT,
  UP,
  LEFT,
  DOWN
};

struct Instruction {
  DIREC direction;
  int steps;
};

struct Position {
  int x;
  int y;

  Position() : x(0), y(0) {}
  Position(int xpos, int ypos) {
    this->x = xpos;
    this->y = ypos;
  }

  bool operator==(const Position& oPoint) const {
    if (this->x == oPoint.x && this->y == oPoint.y) return true;
    else return false;
  }
  
  struct Hash {
    size_t operator()(const Position& pos) const {
      size_t xHash = std::hash<int>()(pos.x);
      size_t yHash = std::hash<int>()(pos.y);
      return xHash ^ yHash;
    }
  };
};


int main() {
  std::ifstream input("fileInput.txt");
  std::string inputLine;
  std::vector<Instruction> instructionTable = {};
  int inputLength = 0;

  std::getline(input, inputLine);
  input.seekg(0, input.end);
  inputLength = input.tellg();
  input.seekg(0, input.beg);

  if (inputLength < 0) { return -1; }

  while (input.tellg() < inputLength) {
    std::getline(input, inputLine);
    
    Instruction ithStep;
    ithStep.steps = std::stoi(inputLine.substr(inputLine.find_last_of(' ') + 1, std::string::npos));
    switch (inputLine.at(0)) {
      case 'R':
        ithStep.direction = RIGHT;
        break;
      case 'U':
        ithStep.direction = UP;
        break;
      case 'L':
        ithStep.direction = LEFT;
        break;
      case 'D':
        ithStep.direction = DOWN;
        break;
    }
    instructionTable.push_back(ithStep);
  }

  Position ropeHead;
  Position ropeTail;
  Position headTrail;
  std::unordered_set<Position, Position::Hash> tailPositions;
  tailPositions.insert({0, 0});

  for (std::vector<Instruction>::iterator it = instructionTable.begin(); it < instructionTable.end(); it++) {
    for (int i = 0; i < it->steps; i++) {
      headTrail = ropeHead;
      switch (it->direction) {
        case RIGHT:
          ropeHead.x++;
          break;
        case UP:
          ropeHead.y++;
          break;
        case LEFT:
          ropeHead.x--;
          break;
        case DOWN:
          ropeHead.y--;
          break;
      }

      if (std::abs(ropeHead.x - ropeTail.x) > 1 || std::abs(ropeHead.y - ropeTail.y) > 1) {
        ropeTail = headTrail;
        tailPositions.insert(ropeTail);
      }
    }
  }

  std::cout << tailPositions.size() << std::endl;

  return 0;
}
