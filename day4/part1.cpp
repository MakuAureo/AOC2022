#include <iostream>
#include <vector>
#include <string>
#include <fstream>

void divideStr(const std::string originalStr, std::string* subStr1, std::string* subStr2, std::size_t dividePos);
std::vector<int> getSortedArrayIntersection(const std::vector<int> array1, const std::vector<int> array2);

int main() {
  std::ifstream input("fileInput.txt");
  std::string inputLine, subString1, subString2, intStr1, intStr2;
  int inputLength, containmentCount = 0;

  input.seekg(0, input.end);
  inputLength = input.tellg();
  input.seekg(0, input.beg);

  while (input.tellg() < inputLength) {
    std::getline(input, inputLine);

    std::vector<int> intArray1 = {}, intArray2 = {};

    divideStr(inputLine, &subString1, &subString2, inputLine.find_first_of(","));

    divideStr(subString1, &intStr1, &intStr2, subString1.find_first_of("-"));
    for (int i = std::stoi(intStr1); i <= std::stoi(intStr2); i++) intArray1.push_back(i);

    divideStr(subString2, &intStr1, &intStr2, subString2.find_first_of("-"));
    for (int i = std::stoi(intStr1); i <= std::stoi(intStr2); i++) intArray2.push_back(i);
    
    std::vector<int> intersection = getSortedArrayIntersection(intArray1, intArray2);
    if (intersection == intArray1) { containmentCount++; }
    else if (intersection == intArray2) { containmentCount++; }
  }

  std::cout << containmentCount << std::endl;
  return 0;
}

void divideStr(const std::string originalStr, std::string* subStr1, std::string* subStr2, std::size_t dividePos) {
  *subStr1 = originalStr.substr(0, dividePos);
  *subStr2 = originalStr.substr(dividePos + 1, (originalStr.length() - 1) - dividePos);
}

std::vector<int> getSortedArrayIntersection(const std::vector<int> array1, const std::vector<int> array2) {
  std::vector<int> arrayIntersection;

  int i = 0, j = 0;
  while (i < array1.size() && j < array2.size()) {
    if (array1.at(i) < array2.at(j)) { i++; }
    else if (array1.at(i) > array2.at(j)) { j++; }
    else if (array1.at(i) == array2.at(j)) {
      arrayIntersection.push_back(array1.at(i));
      i++;
      j++;
    }
  }

  return arrayIntersection;
}
