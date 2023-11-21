#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<int> sortIntList(std::vector<int>& list);

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string string;
  std::vector<int> sumList;
  int currentSum = 0;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);
    //Get sum
    if (!string.empty()) { currentSum += std::stoi(string); }
    //Update sumList
    else {
      sumList.push_back(currentSum);
      currentSum = 0;
    }
  }

  //Sort results (smallest to biggest)
  sumList = sortIntList(sumList);

  //Print 3 biggest elements
  for (std::vector<int>::reverse_iterator it = sumList.rend(); it != sumList.rbegin() - 3; it++) { std::cout << *it << '\n'; }
  std::cout << std::endl;

  return 0;
}

std::vector<int> sortIntList(std::vector<int>& list) {
  //This is my version of quicksort (recursive)
  if (list.size() < 2)
    return list;
  
  std::vector<int> sortedList;
  int repeatPiv = 0;
  int pivot = list.at(std::floor(list.size()/2));

  std::vector<int> list1, list2;
  for (std::vector<int>::iterator i = list.begin(); i != list.end(); i++) {
    if (*i < pivot) { list1.push_back(*i); }
    else if (*i > pivot) { list2.push_back(*i); }
    else if (*i == pivot) { repeatPiv++; }
  }

  list1 = sortIntList(list1);
  list2 = sortIntList(list2);

  sortedList = list1;
  for (int i = 0; i < repeatPiv; i++) { sortedList.push_back(pivot); }
  sortedList.insert(sortedList.end(), list2.begin(), list2.end());

  return sortedList;
}
