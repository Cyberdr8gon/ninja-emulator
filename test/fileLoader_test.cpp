#include "gtest/gtest.h"
#include "fileLoader.h"

TEST (fileLoader_tests, returnsNullOnBadFilename)
{
  char* test = "BLAH";
  ASSERT_FALSE(fileLoader(test));
}