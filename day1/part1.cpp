#include <iostream>
#include <fstream>
#include <string>

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string string;
  int currentSum = 0;
  int biggestElement = 0;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);
    //Get sum
    if (string.length()) { currentSum += std::stoi(string); }
    //Update currentSum and biggestElement
    else if (!string.length()) {
      if (currentSum > biggestElement) biggestElement = currentSum;
      currentSum = 0;
    }
  }

  //Print biggestElement
  std::cout << biggestElement << std::endl;

  return 0;
}
