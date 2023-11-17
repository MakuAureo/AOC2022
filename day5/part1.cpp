#include <iostream>
#include <fstream>
#include <string>
#include <vector>

///Note to self:
///  It's kinda funny that the most complex one so far didn't use functions, I wonder
///  if I've been using them unnecessarily or this didn't have a lot of repetition

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string str;
  int inputLength;

  //Get input size
  input.seekg(0, input.end);
  inputLength = input.tellg();
  input.seekg(0, input.beg);

  //The first few lines of the fileInput are the setup so they must be handled differently
  //This gets how many stacks of crates are in the input so even if the input had more or
  //less than 9 stacks it would still work as long as it had the same formating
  std::getline(input, str);
  int stacks = (str.length()+1)/4;

  //Matrix (array of arrays) that stores where each crate is (lines (1st access) are the stack
  //and rows (2nd access) are the position within the stack
  std::vector<std::vector<char>> crateMatrix;
  crateMatrix.resize(stacks, {});

  //Populate the crateMatrix
  while (str.at(0) != ' ') { //This condition checks if the line with the number of stacks has been reached
    //Since the order in which they're accessed is top to bottom (end to begging) new elements
    //must be placed at the start
    for (int i = 0; i < stacks; i++) { if (str.at(4*i + 1) != ' ') { crateMatrix.at(i).insert(crateMatrix.at(i).begin(),str.at(4*i + 1)); } }
    std::getline(input, str);
  }

  //This moves the line to the empty string just before the instructions
  std::getline(input, str);

  //Extract instruction data
  while (input.tellg() < inputLength) {
    std::getline(input, str);
    
    //Find how many, to and from where crates must be moved by looking at where the numbers start and end
    std::vector<std::size_t> idxArray = {0, 0, 0, 0, 0};
    idxArray.at(0) = str.find(' ');
    for (std::vector<std::size_t>::iterator it = idxArray.begin() + 1; it != idxArray.end(); it++) {
      *it = str.find(' ', *(it - 1) + 1);
    }

    std::string substr = str.substr(idxArray.at(0) + 1, idxArray.at(1) - idxArray.at(0) - 1);
    int moveAmount = std::stoi(substr);

    substr = str.substr(idxArray.at(2) + 1, idxArray.at(3) - idxArray.at(2) - 1);
    int moveFrom = std::stoi(substr);

    substr = str.substr(idxArray.at(4) + 1, str.length() - idxArray.at(4) - 1);
    int moveTo = std::stoi(substr);

    //Peform the operation
    std::vector<char>::reverse_iterator it = crateMatrix.at(moveFrom - 1).rbegin();
    for (int i = 0; i < moveAmount; i++) {
      crateMatrix.at(moveTo - 1).push_back(*(it++));
      crateMatrix.at(moveFrom - 1).pop_back();
    }
  }
  
  //Output result
  for (std::vector<std::vector<char>>::iterator it = crateMatrix.begin(); it != crateMatrix.end(); it++) {
    std::cout << (*it).back();
  }
  std::cout << std::endl;

  return 0;
}
