#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "Movie.hpp"

using namespace std;
using namespace testing;

class SimpleMovieFixture : public ::testing::Test {
  protected:
  public:
    SimpleMovieFixture() {
        // initialization code here
    }
};
TEST_F(SimpleMovieFixture, TEST_BFS) {}