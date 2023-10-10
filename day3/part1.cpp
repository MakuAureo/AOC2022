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
  std::string string, compartment1, compartment2;
  std::vector<int> intArray1, intArray2, intIntersection, intersectionList;
  int i = 0;

  //Get input size
  input.seekg(0, input.end);
  int inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, string);

    //Break the rucksack (original string) into 2 compartments (2 new strings)
    compartment1.insert(compartment1.end(), string.begin(), string.begin() + string.length()/2);
    compartment2.insert(compartment2.end(), string.end() - string.length()/2, string.end());

    //Convert strings to int vectors
    intArray1 = convertCharStringToIntArray(&compartment1);
    intArray2 = convertCharStringToIntArray(&compartment2);

    //Sort to make the intersection operation faster
    intArray1 = sortIntArray(&intArray1);
    intArray2 = sortIntArray(&intArray2);

    //Get intersection and store them in a list
    intIntersection = getSortedIntArrayIntersection(&intArray1, &intArray2);
    intersectionList.insert(intersectionList.end(), intIntersection.begin(), intIntersection.end());

    //Reset compartment strings
    compartment1 = "";
    compartment2 = "";
  }

  //Since the input had already been converted into a integer list casting 'char' as 'int' returns
  //their ASCII code (97 to 122 for a to z and 65 to 90 for A to Z) getting each letters priority
  //is as simple as adding/subtracting
  int prioritySum = 0;
  for (std::vector<int>::iterator it = intersectionList.begin(); it != intersectionList.end(); it++) {
    if (*it < 91) prioritySum += (*it - 38);
    else if (*it > 96) prioritySum += (*it - 96);
  }

  //Output result
  std::cout << prioritySum << std::endl;

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
