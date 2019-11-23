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
    string name;
    vector<Movie*> movies;

    // for BFS
    int dist;
    Actor* prev_actor;
    Movie* prev_movie;
    Actor(string name) : name(name){};
    ~Actor();
};

#endif