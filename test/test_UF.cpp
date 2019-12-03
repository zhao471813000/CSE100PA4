#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"
#include "UF.hpp"
using namespace std;
using namespace testing;

class SmallUFFixture : public ::testing::Test {
  protected:
    UF uf;

  public:
};

TEST_F(SmallUFFixture, TEST_Functions) {
    ActorGraph actorGraph;
    actorGraph.buildGraph("KB", "first", 2011);
    actorGraph.buildGraph("JM", "first", 2011);
    actorGraph.buildGraph("JM", "ap", 2016);
    actorGraph.buildGraph("JM", "glass", 2019);
    actorGraph.buildGraph("MF", "first", 2011);
    actorGraph.buildGraph("MF", "ap", 2016);
    actorGraph.buildGraph("MF", "alien", 2017);
    actorGraph.buildGraph("SL", "glass", 2019);
    actorGraph.buildGraph("SL", "avengers", 2019);
    actorGraph.buildGraph("RB", "avengers", 2019);
    actorGraph.buildGraph("RB", "spider", 2017);
    actorGraph.buildGraph("TH", "spider", 2017);
    actorGraph.buildGraph("TH", "war", 2017);
    actorGraph.buildGraph("KW", "alien", 2017);
    actorGraph.buildGraph("KW", "war", 2017);

    Actor* kb = actorGraph.actors["KB"];
    Actor* jm = actorGraph.actors["JM"];
    Actor* mf = actorGraph.actors["MF"];
    Actor* sl = actorGraph.actors["SL"];
    Actor* th = actorGraph.actors["TH"];
    Actor* kw = actorGraph.actors["KW"];
    Actor* rd = actorGraph.actors["RB"];

    uf.connect(kb, jm);
    uf.connect(kb, mf);
    ASSERT_EQ(uf.connected(jm, mf), true);
    ASSERT_EQ(uf.find(kb), jm);
}