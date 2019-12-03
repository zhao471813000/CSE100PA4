#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "Actor.hpp"
#include "Edge.hpp"
#include "Movie.hpp"

using namespace std;
using namespace testing;

class SimpleEdgeFixture : public ::testing::Test {
  protected:
    Edge* edge;

  public:
    SimpleEdgeFixture() {
        // initialization code here
        Movie* movie = new Movie("m", 2019, 1);
        Actor* actor1 = new Actor("a1");
        Actor* actor2 = new Actor("a2");
        edge = new Edge(movie->weight, movie, actor1, actor2);
    }
};
TEST_F(SimpleEdgeFixture, TEST_CONSTRUCTOR) { ASSERT_EQ(1, edge->weight); }