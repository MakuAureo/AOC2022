#include <iostream>
#include <string>
#include <fstream>
#include "Directory.hpp"

///Note:
///  This is probably the most complex and time consuming thing I've done this far and looking back there are many things
///  I could've done better and faster, but the amount of concepts I learned surely made up for that.
///  Maybe I'll start this over using standard modern c++ practices like unique and shared pointers, linked lists

enum STATE {
  _COMMAND,
  _DIR,
  _FILE,
  END
};

//Part2.cpp special function
unsigned int Directory::findSmallestDirectorySizeToDelete(unsigned int sizeFreeSpaceNeeded) {
  static const unsigned int freeMemory = 70000000 - memorySize;
  static unsigned int dirSize = memorySize;

  if (memorySize + freeMemory > sizeFreeSpaceNeeded && memorySize < dirSize) { dirSize = memorySize; }
  for (int i = 0; i < directoryCount; i++) { directories[i]->findSmallestDirectorySizeToDelete(sizeFreeSpaceNeeded); }

  return dirSize;
}

int main() {
  //Inital declarations
  std::ifstream input("fileInput.txt");
  Directory root;
  std::string path = "root";
  std::string inputString;
  int inputLength;
  std::string dirName;

  //Get input size
  input.seekg(0, input.end);
  inputLength = input.tellg();
  input.seekg(0, input.beg);

  //Skip first line
  std::getline(input, inputString);

  //Extract input data
  while (input.tellg() < inputLength) {
    std::getline(input, inputString);
    STATE line;
    unsigned int first_ = inputString.find_first_of(' '), last_ = inputString.find_last_of(' ');
    std::string sub = inputString.substr(0, first_);
    
    //Check if current line is a command, a file, a directory or end of file
    if (sub == "$") { line = _COMMAND; }
    else if (sub == "dir") { line = _DIR; }
    else if (sub.find_first_of("123456789") == 0) { line = _FILE; }
    else { line = END; }

    //Each state interprets the current line differently
    switch (line) {
      case _COMMAND:
        //Skips "$ ls"
        if (inputString.substr(2, 2) == "cd") {
          //Update current directory name to be accessed
          dirName = inputString.substr(last_ + 1, std::string::npos);
          //If dirName is .., drop current directory from path
          if (dirName == "..") { path = path.substr(0, path.find_last_of('/')); }
          //If not append /dirName to path
          else { path.append("/" + dirName); }
        }
        break;
      case _FILE:
        //New file at current path
        root.newFile(inputString.substr(last_ + 1, std::string::npos), std::stoi(sub), path);
        break;
      case _DIR:
        //New dir at current path
        dirName = inputString.substr(last_ + 1, std::string::npos);
        root.newDirectory(dirName, path);
        break;
      case END:
        //End of file
        break;
    }
  }

  //Output result
  std::cout << root.findSmallestDirectorySizeToDelete(30000000) << std::endl;

  return 0;
}
