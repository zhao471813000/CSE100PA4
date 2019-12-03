/*
 * UF.cpp
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585
 *
 * This file is meant to find the MST of the actor graph using disjoint sets.
 */

#include "UF.hpp"
#include <fstream>
#include <iostream>
#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;

/** Connects two nodes if they are not already connected.
 *  Union by weight(rank).
 */
void UF::connect(Actor* actor1, Actor* actor2) {
    if (connected(actor1, actor2)) {
        return;
    }
    Actor* sentinel1 = find(actor1);
    Actor* sentinel2 = find(actor2);
    if (sentinel1->rank > sentinel2->rank) {
        sentinel2->parent = sentinel1;
        sentinel1->rank += sentinel2->rank;
    } else {
        sentinel1->parent = sentinel2;
        sentinel2->rank += sentinel1->rank;
    }
}

/** Return true if two actors are connected, and false otherwise. */
bool UF::connected(Actor* actor1, Actor* actor2) {
    return find(actor1)->name == find(actor2)->name;
}

/** Find returns the sentinel node of the up-tree.
 *  Path compression is used.
 */
Actor* UF::find(Actor* actor) {
    Actor* curr = actor;
    while (curr->parent != nullptr) {
        curr = curr->parent;
    }
    Actor* sentinel = curr;
    // path compression
    curr = actor;
    Actor* temp;
    while (curr->parent != nullptr) {
        temp = curr->parent;
        curr->parent = sentinel;
        curr = temp;
    }
    return sentinel;
}