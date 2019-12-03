/**
 * Implements an actor class to represent node in graph.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <iostream>
#include <limits>
#include <vector>
#include "Movie.hpp"
using namespace std;

class Movie;
/* Implements an actor class, which is node in actorGraph. */
class Actor {
  private:
  public:
    // connect by rank
    int rank;

    string name;
    vector<Movie*> movies;
    bool done;
    unordered_map<Actor*, int> edgeNum;

    int dist;  // for BFS
    Actor* prev_actor;
    Movie* prev_movie;

    Actor* parent;

    Actor(string name) : name(name) {
        // initialize for MST
        rank = 1;
        parent = nullptr;
    };
};

#endif