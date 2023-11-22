#include <iostream>
#include <fstream>
#include <string>

///Note: 
///  This looks horrible and I'd like to do it in a clever way
///  but I didn't find any such methods

int main() {
  //Initial declarations
  std::ifstream input("fileInput.txt");
  std::string inputLine;
  int inputLength;

  //Get input size
  input.seekg(0, input.end);
  inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Get height matrix size
  std::getline(input, inputLine);
  const int rowSize = inputLine.length(), columnSize = inputLength/inputLine.length() - 1;
  
  //Make 2 matrices, one to store the heights and the other to store if the tree in that
  //position is visible or not
  int treeHeightMatrix[columnSize][rowSize];
  bool isVisible[columnSize][rowSize];

  //Reset inputFile
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    //Iterate over each column
    for (int j = 0; j < columnSize; j++) {
    //Update current column (new line from file)
    std::getline(input, inputLine);

      //Iterate over line characters
      for (int i = 0; i < rowSize; i++) {
        //Populate both matrices
        isVisible[j][i] = true;
        treeHeightMatrix[j][i] = (inputLine.at(i) - '0'); //Cool trick to convert a char of a digit to int in-line
      } 
    }
  }

  //For each element of the height matrix
  for (int j = 1; j < columnSize - 1; j++) {
    for (int i = 1; i < rowSize - 1; i++) {
      //Assume it's visible from every side
      bool isVisibleUp = true;
      bool isVisibleLeft = true;
      bool isVisibleDown = true;
      bool isVisibleRight = true;

      //Look at all the elements in the same column before it
      for (int k = 0; k < j; k++) {
        //If they are shorter than any of those elements the for will break and isVisible(Direction) is set to false
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[k][i]) {
          isVisibleUp = false;
          break;
        }
      }
      //Same thing 4 times
      for (int k = 0; k < i; k++) {
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[j][k]) {
          isVisibleLeft = false;
          break;
        }
      }
      for (int k = columnSize - 1; k > j; k--) {
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[k][i]) {
          isVisibleDown = false;
          break;
        }
      }
      for (int k = rowSize - 1; k > i; k--) {
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[j][k]) {
          isVisibleRight = false;
          break;
        }
      }

      //A tree is visible if it's visible from any side, so doing a 4-way OR operation will be true if any of them are true
      isVisible[j][i] = (isVisibleUp || isVisibleLeft || isVisibleDown || isVisibleRight);
    }
  }

  //Get sum
  int sum = 0;
  for (int j = 0; j < columnSize; j++) {
    for (int i = 0; i < rowSize; i++) {
      //1 only if visible, 0 otherwise
      sum += isVisible[j][i];
    }
  }

  //Output result
  std::cout << sum << std::endl;

  return 0;
}
