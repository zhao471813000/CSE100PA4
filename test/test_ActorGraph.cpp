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
    // SmallActorGraphFixture() {
    // initialization code here
    // const char* in_filename = "data/imdb_small_sample.tsv";
    // actorGraph.loadFromFile(in_filename, false);
    // unordered_map<string, Actor*> actors = actorGraph.getActors();
    // unordered_map<string, Movie*> movies = actorGraph.getMovies();
    // }
};
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

    Movie* m1 = new Movie("first", 2011);
    Movie* m2 = new Movie("ap", 2012);
    Movie* m3 = new Movie("glass", 2011);
    Movie* m4 = new Movie("alien", 2019);
    Movie* m5 = new Movie("avengers", 2011);
    Movie* m6 = new Movie("spider", 2015);
    Movie* m7 = new Movie("war", 2010);
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
}