#include <fstream>
#include "fileLoader.h"


char* fileLoader(char* filename) {
  std::streampos size;
  char* fileInMemory;

  std::ifstream fileHandle(filename, std::ios::in | std::ios::binary | std::ios::ate);
  if(fileHandle.is_open())
  {
    size = fileHandle.tellg();
    fileInMemory = new char[size];
    fileHandle.seekg(0, std::ios::beg);
    fileHandle.read(fileInMemory, size);
    fileHandle.close();
    return fileInMemory;
  }
  else
  {
    return NULL;
  }
}
