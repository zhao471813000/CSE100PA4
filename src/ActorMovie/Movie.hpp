/**
 * Implements a movie class to represent node in graph.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Actor.hpp"

using namespace std;
class Actor;
/* Implements a movie class. */
class Movie {
  public:
    string name;
    vector<Actor*> actors;
    int year;
    Movie(string name, int year) : name(name), year(year){};
};

#endif