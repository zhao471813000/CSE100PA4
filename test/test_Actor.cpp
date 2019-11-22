#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "Actor.hpp"

using namespace std;
using namespace testing;

class SimpleActorFixture : public ::testing::Test {
  protected:
  public:
    SimpleActorFixture() {
        // initialization code here
    }
};
TEST_F(SimpleActorFixture, TEST_CONSTRUCTOR) {}