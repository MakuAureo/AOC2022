#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

//This thing is atrocious, but I love it

#include <iostream>
#include <string>

const int CONST_MAX_DIR_SIZE = 64;
const int CONST_MAX_FILE_SIZE = 64;

struct file {
  std::string name;
  unsigned int size;
};

class Directory{
private:
  //Internal data
  std::string name;
  unsigned int memorySize = 0, fileCount = 0, directoryCount = 0;
  const int MAX_FILE_SIZE, MAX_DIR_SIZE;
  file* files = new file[MAX_FILE_SIZE];
  Directory** directories = new Directory*[MAX_DIR_SIZE];
  Directory* parentDirectory;

  //This constructor will only ever be used to make directories inside root directory, thus ensuring only root directory has nullptr as parent
  Directory(const std::string name, Directory* parent) : name(name), MAX_DIR_SIZE(CONST_MAX_DIR_SIZE), MAX_FILE_SIZE(CONST_MAX_FILE_SIZE) { parentDirectory = parent; };

  //Update size of current directory and trigger size update for parent directory
  void updateSize() {
    memorySize = 0;
    for (file* it = files; it < files + fileCount; it++) { memorySize += (*it).size; }
    for (Directory** it = directories; it < directories + directoryCount; it++) { memorySize += (**it).memorySize; }
    if (parentDirectory) { parentDirectory->updateSize(); }
  }

  //Directory search: return a pointer to directory named 'dirName' whithin current directory, if no such directory exists return nullptr
  Directory* searchForDirectory(std::string dirName) {
    Directory* location = nullptr;

    for (int i = 0; i < directoryCount; i++) { if ((directories[i])->name == dirName) { location = (directories)[i]; } }

    return location;
  }

  //Construct new directory named 'name' within current directory
  void newDirectory(const std::string name){
    if (searchForDirectory(name) != nullptr) {
      std::cout << "Directory with name: " << name << " already exists in " << this->name << " unable to make new directory\n";
      return;
    }

    Directory dir(name, this);
    directories[directoryCount] = new Directory;
    *(directories[directoryCount++]) = dir;
  }

  //Create new file named 'name' with size 'size' within current directory
  void newFile(const std::string name, const unsigned int size) {
    (files[fileCount]).name = name;
    (files[fileCount++]).size = size;
    
    //Trigger size update
    updateSize();
  }

public:
  //Constructors: named "root" or 'dirName' and nullptr as parentDirectory (only root is allowed to use this constructor)
  Directory() : name("root"), MAX_DIR_SIZE(CONST_MAX_DIR_SIZE), MAX_FILE_SIZE(CONST_MAX_FILE_SIZE) { parentDirectory = nullptr; };
  Directory(const std::string dirName) : name(dirName), MAX_DIR_SIZE(CONST_MAX_DIR_SIZE), MAX_FILE_SIZE(CONST_MAX_FILE_SIZE) { parentDirectory = nullptr; };

  //Destructor: delete allocated memory
  ~Directory() {
    //First delete child directories and point to null after
    for (int i = 0; i < directoryCount; i++) {
      delete directories[i];
      directories[i] = nullptr;
    }
    //Then delete directory and file arrays and point to null after
    delete[] directories;
    directories = nullptr;
    delete[] files;
    files = nullptr;
  }

  //Copy assingment operator: copy internal properties from other
  Directory& operator=(const Directory& other) {
    name = other.name;
    memorySize = other.memorySize;
    fileCount = other.fileCount;
    directoryCount = other.directoryCount;
    parentDirectory = other.parentDirectory;

    for (int i = 0; i < other.fileCount; i++) { files[i] = other.files[i]; }
    for (int i = 0; i < other.directoryCount; i++) { *(directories[i]) = *(other.directories[i]); }

    return *this;
  }

  //Create new directory using 'path' as path instruction
  void newDirectory(const std::string name, const std::string path) {
    std::string substr = path;
    std::size_t match = path.find_first_of('/');
    Directory* pDir = this;

    //While there are subdirectories in 'substr'
    while (match != std::string::npos) {
      //If search fails
      if (pDir == nullptr) {
        std::cout << "unable to find given path at " << substr << '\n';
      }
      //Cut current parent directory
      substr = substr.substr(match + 1, std::string::npos);
      match = substr.find_first_of('/');

      //Update directory pointer to sub directory
      std::string currentDirectoryName = substr.substr(0, match);
      pDir = pDir->searchForDirectory(currentDirectoryName);
    }
    
    //Construct directory
    pDir->newDirectory(name);
  }

  //Create new file of size 'size' using 'path' as path instruction
  void newFile(const std::string name, const unsigned int size, const std::string path) {
    std::string substr = path;
    std::size_t match = path.find_first_of('/');
    Directory* pDir = this;

    //While there are subdirectories in 'substr'
    while (match != std::string::npos) {
      if (pDir == nullptr) {
        std::cout << "unable to find given path at " << substr << '\n';
      }
      //Cut current parent directory
      substr = substr.substr(match + 1, std::string::npos);
      match = substr.find_first_of('/');

      //Update directory pointer to sub directory
      std::string currentDirectoryName = substr.substr(0, match);
      pDir = pDir->searchForDirectory(currentDirectoryName);
    }
    
    //Create new file
    pDir->newFile(name, size);
  }

  //Display directory contents as a file tree
  void contents(int indent = 1) {
    if (!parentDirectory) { std::cout << this->name << " : " << this->memorySize << '\n'; }
    std::string indentation(indent, '|');
    for (int i = 0; i < fileCount; i++) {
      std::cout << indentation << ' ' << (files[i]).name << " : " << (files[i]).size << '\n';
    }
    for (int i = 0; i < directoryCount; i++) {
      std::cout << indentation << '+' << (*(directories[i])).name << " : " << (*(directories[i])).memorySize << '\n';
      (*(directories[i])).contents(indent+1);
    }
  }

  //Special functions defined in part1.cpp and part2.cpp
  unsigned int sumSizesLessThan(unsigned int size);
  unsigned int findSmallestDirectorySizeToDelete(unsigned int freeSpaceNeeded);
};

#endif //DIRECTORY_HPP
