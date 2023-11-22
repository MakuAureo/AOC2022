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
  
  //Make 2 matrices, one to store the heights and the other to store their scenic score
  int treeHeightMatrix[columnSize][rowSize];
  int treeScenicScore[columnSize][rowSize];

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
        treeScenicScore[j][i] = 0;
        treeHeightMatrix[j][i] = (inputLine.at(i) - '0'); //Cool trick to convert a char of a digit to int in-line
      } 
    }
  }

  //For each element of the height matrix
  for (int j = 1; j < columnSize - 1; j++) {
    for (int i = 1; i < rowSize - 1; i++) {
      int scoreUp = 0;
      int scoreLeft = 0;
      int scoreDown = 0;
      int scoreRight = 0;

      //Look at the element from column j, line i outward and increment score
      for (int k = j - 1; k >= 0; k--) {
        scoreUp++;
        //If a tree taller than or of equal height break the for loop
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[k][i]) {
          break;
        }
      }
      //Same thing 4 times
      for (int k = i - 1; k >= 0; k--) {
        scoreLeft++;
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[j][k]) {
          break;
        }
      }
      for (int k = j + 1; k < columnSize; k++) {
        scoreDown++;
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[k][i]) {
          break;
        }
      }
      for (int k = i + 1; k < rowSize; k++) {
        scoreRight++;
        if (treeHeightMatrix[j][i] <= treeHeightMatrix[j][k]) {
          break;
        }
      }

      //Total score is the product of all scores
      treeScenicScore[j][i] = scoreUp * scoreLeft * scoreDown * scoreRight;
    }
  }

  //Find highestScore
  int highestScore = 0;
  for (int j = 0; j < columnSize; j++) {
    for (int i = 0; i < rowSize; i++) {
      //Update current highest score if a bigger score is found
      if (treeScenicScore[j][i] > highestScore) { highestScore = treeScenicScore[j][i]; }
    }
  }

  //Output result
  std::cout << highestScore << std::endl;

  return 0;
}
