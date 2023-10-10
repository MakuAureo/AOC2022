#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

std::vector<int> convertCharStringToIntArray(const std::string* charString);
std::vector<int> sortIntArray(const std::vector<int>* intArray);
std::vector<int> getSortedIntArrayIntersection(const std::vector<int>* array1, const std::vector<int>* array2);

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::string string;
  std::string* rucksacks = new std::string[3];
  std::vector<int> intIntersection, intersectionList;
  std::vector<int>* intArrays = new std::vector<int>[3];
  int lines = 0;
  int i = 0;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);
    //Keep track of the line count
    lines++;

    //Since 3 lines are needed, strings are stored until lines is a multiple of 3
    switch (lines%3) {
      case 1:
        *rucksacks = string;
        break;
      
      case 2:
        *(rucksacks + 1) = string;
        break;
      
      case 0:
        *(rucksacks + 2) = string;

        //Convert to string and sort the intArrays
        for (int i = 0; i < 3; i++) { 
          *(intArrays + i) = convertCharStringToIntArray(rucksacks + i);
          *(intArrays + i) = sortIntArray(intArrays + i);
        }

        //The intersection of 3 lists is the intersection of one of them with the intersection
        //of the other 2, the temporary int array is not needed, but makes the code more readable
        std::vector<int> temp = getSortedIntArrayIntersection(intArrays, intArrays+1);
        intIntersection = getSortedIntArrayIntersection(&temp, intArrays+2);
        
        intersectionList.insert(intersectionList.end(), intIntersection.begin(), intIntersection.end());
        break;
    }

  }

  //Compute the priority sum
  int prioritySum = 0;
  for (std::vector<int>::iterator it = intersectionList.begin(); it != intersectionList.end(); it++) {
    if (*it < 91) prioritySum += (*it - 38);
    else if (*it > 96) prioritySum += (*it - 96);
  }

  //Output result
  std::cout << prioritySum << std::endl;

  //Delete anything created with 'new' to prevent memory leaks
  delete[] rucksacks;
  delete[] intArrays;
  
  return 0;
}

std::vector<int> convertCharStringToIntArray(const std::string* charString) {
  std::vector<int> intArray;
  
  for (int i = 0; i < charString->length(); i++) {
    intArray.insert(intArray.end(), static_cast<int>(charString->at(i)));
  }

  return intArray;
}

std::vector<int> sortIntArray(const std::vector<int>* intArray) {
  //Quicksort (no repeats)
  if (intArray->size() < 2) return *intArray;

  std::vector<int> sortedArray;
  int pivot = intArray->at(std::floor(intArray->size()/2));

  std::vector<int> array1, array2;

  for (std::vector<int>::const_iterator it = intArray->begin(); it != intArray->end(); it++) {
    if (*it < pivot) array1.push_back(*it);
    else if (*it > pivot) array2.push_back(*it);
  }

  array1 = sortIntArray(&array1);
  array2 = sortIntArray(&array2);

  sortedArray = array1;
  sortedArray.push_back(pivot);
  sortedArray.insert(sortedArray.end(), array2.begin(), array2.end());

  return sortedArray;
}

std::vector<int> getSortedIntArrayIntersection(const std::vector<int>* array1, const std::vector<int>* array2) {
  std::vector<int> intArrayIntersection;

  int i = 0;
  int j = 0;
  while (i < array1->size() && j < array2->size()) {
    //When doing intersections of int arrays you can cut down on the number of comparisons if they
    //are sorted since once you know that the array is ordered and the next elements are always bigger
    //or smaller than the current element
    if (array1->at(i) < array2->at(j)) { i++; }
    else if (array1->at(i) > array2->at(j)) { j++; }
    else { 
      intArrayIntersection.push_back(array1->at(i));
      i++;
      j++;
    }
  }

  return intArrayIntersection;
}
