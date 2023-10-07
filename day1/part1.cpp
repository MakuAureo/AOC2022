#include <iostream>
#include <fstream>
#include <string>

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string string;
  int currentSum = 0;
  int biggestElement;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);
    //Get sum
    if (string.length()) { currentSum += std::stoi(string); }
    //Update biggestElement
    else if (!string.length() && currentSum > biggestElement) { biggestElement = currentSum; }
  }

  //Print biggestElement
  std::cout << biggestElement << std::endl;

  return 0;
}
