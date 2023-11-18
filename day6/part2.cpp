#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

///Note to self:
///  while this solution is short (very short in fact) I'm not sure
///  it is a good one, I have no experience with sets and as such
///  have no ideia how efficient they are in code

///Note to self2:
///  this is the least I had to change from part1 to part2 (added a
///  '1' to line 20) and I doubt this is gonna change

int main() {
  //Initial declaration
  std::ifstream input("fileInput.txt");
  std::unordered_set<char> strSet;
  std::string inputString;
  int markerSize = 14;

  //Extract input string
  std::getline(input, inputString);

  //Iterate over the string
  int pos = 0;
  for (; pos < inputString.size() - markerSize; pos++) {
    //Looking at 4 characters at a time
    std::string substr = inputString.substr(pos, markerSize);

    //Pass them to a set
    strSet.insert(substr.begin(), substr.end());
    //If the has size == markerSize then the substr must be
    //all different characters
    if (strSet.size() == markerSize) { break; }
    else { strSet.clear(); }
  }

  //Output result
  std::cout << pos + markerSize << std::endl;

  return 0;
}
