#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "Actor.hpp"

using namespace std;
using namespace testing;

class SimpleActorFixture : public ::testing::Test {
  protected:
    Actor* actor;

  public:
    SimpleActorFixture() { actor = new Actor("Kevin Bacon"); }
};
TEST_F(SimpleActorFixture, TEST_CONSTRUCTOR) {
    ASSERT_EQ("Kevin Bacon", actor->name);
}