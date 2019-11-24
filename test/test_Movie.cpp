#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "Movie.hpp"

using namespace std;
using namespace testing;

class SimpleMovieFixture : public ::testing::Test {
  protected:
    Movie* movie;

  public:
    SimpleMovieFixture() {
        // initialization code here
        movie = new Movie("Joker", 2019);
    }
};
TEST_F(SimpleMovieFixture, TEST_CONSTRUCTOR) {
    ASSERT_EQ("Joker", movie->name);
    ASSERT_EQ(2019, movie->year);
}