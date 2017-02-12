// be sure to remove this as it is extremely taxing for performance
#include <iostream>


#include "fileLoader.h"

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;
  if(argc == 1)
  {
    std::cout << "GUI file selection not yet implemented" << std::endl;
  }


  char* rom_data = fileLoader(argv[1]);


  // processor

}
