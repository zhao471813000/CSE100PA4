#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "ActorGraph.hpp"

using namespace std;
using namespace testing;

class SmallActorGraphFixture : public ::testing::Test {
  protected:
    ActorGraph actorGraph;

  public:
};

TEST_F(SmallActorGraphFixture, TEST_LOADFROMGRAPH) {
    const char* in_filename = "data/imdb_small_sample.tsv";
    actorGraph.loadFromFile(in_filename, false);
}

TEST_F(SmallActorGraphFixture, TEST_BUILDGRAPH) {
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
    // test bfs
    actorGraph.BFS(kb);
    ASSERT_EQ(kb->dist, 0);
    ASSERT_EQ(mf->dist, 1);
    ASSERT_EQ(jm->dist, 1);

    // test Dijkstra
    actorGraph.Dijkstra(kb);
    ASSERT_EQ(mf->dist, 9);
    ASSERT_EQ(jm->dist, 9);
    ASSERT_EQ(kw->dist, 12);
    ASSERT_EQ(th->dist, 14);
    ASSERT_EQ(rd->dist, 11);
    ASSERT_EQ(sl->dist, 10);
}

TEST_F(SmallActorGraphFixture, TEST_BFS) {
    Actor* kb = new Actor("KB");
    Actor* jm = new Actor("JM");
    Actor* mf = new Actor("MF");
    Actor* kw = new Actor("KW");
    Actor* th = new Actor("TH");
    Actor* rd = new Actor("RD");
    Actor* sl = new Actor("SL");
    actorGraph.actors = {{"KB", kb}, {"JM", jm}, {"MF", mf}, {"KW", kw},
                         {"TH", th}, {"RD", rd}, {"SL", sl}};

    Movie* m1 = new Movie("first", 2011, 0);
    Movie* m2 = new Movie("ap", 2012, 0);
    Movie* m3 = new Movie("glass", 2011, 0);
    Movie* m4 = new Movie("alien", 2019, 0);
    Movie* m5 = new Movie("avengers", 2011, 0);
    Movie* m6 = new Movie("spider", 2015, 0);
    Movie* m7 = new Movie("war", 2010, 0);
    actorGraph.movies = {{"first", m1}, {"ap", m2},       {"glass", m3},
                         {"alien", m4}, {"avengers", m5}, {"spider", m6},
                         {"war", m7}};

    kb->movies = {m1};
    jm->movies = {m1, m2, m3};
    mf->movies = {m1, m2, m4};
    kw->movies = {m4, m7};
    th->movies = {m6, m7};
    rd->movies = {m5, m6};
    sl->movies = {m3, m5};

    m1->actors = {kb, jm, mf};
    m2->actors = {jm, mf};
    m3->actors = {jm, sl};
    m4->actors = {mf, kw};
    m5->actors = {sl, rd};
    m6->actors = {rd, th};
    m7->actors = {kw, th};

    actorGraph.BFS(kb);
    ASSERT_EQ(kb->dist, 0);
    ASSERT_EQ(sl->dist, 2);

    unordered_set<Actor*> firstLevel;
    unordered_set<Actor*> secondLevel;
    actorGraph.levelBFS(kb, firstLevel, secondLevel);
    unordered_set<Actor*> expectedFirstLevel;
    expectedFirstLevel.insert(jm);
    expectedFirstLevel.insert(mf);
    unordered_set<Actor*> expectedSecondLevel;
    expectedSecondLevel.insert(kw);
    expectedSecondLevel.insert(sl);
    ASSERT_EQ(firstLevel, expectedFirstLevel);
    ASSERT_EQ(secondLevel, expectedSecondLevel);
}