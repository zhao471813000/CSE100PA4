#ifndef Edge_HPP
#define Edge_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;
class Movie;
class Actor;
/**
 * Edge class specifies the edge used in graph.
 */
class Edge {
  protected:
  public:
    int weight;
    Movie* movie;
    Actor* actor1;
    Actor* actor2;

    /** Constuctor of Edge. */
    Edge(int weight, Movie* movie, Actor* actor1, Actor* actor2)
        : weight(weight), movie(movie), actor1(actor1), actor2(actor2) {}

    /** Destructor of Edge */
    ~Edge();
};
#endif