#ifndef UF_HPP
#define UF_HPP

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

/**
 * UF class builds the spanning tree and applies different
 * operations to it.
 */
class UF {
  protected:
  public:
    /** Constuctor. */
    UF(void) {}

    /** Destructor. */
    ~UF() {}

    /** Connects two nodes if they are not already connected. */
    void connect(Actor* actor1, Actor* actor2);

    /** Return true if two actors are connected, and false otherwise. */
    bool connected(Actor* actor1, Actor* actor2);

    /** Find returns the sentinel node of the up-tree. */
    Actor* find(Actor* actor);
};
#endif