/*
 * ActorGraph.hpp
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585
 * Date:   <11/21/2019>
 *
 * This file is meant to exist as a container to read the input file format
 * defined in imdb_2019.tsv.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Actor.hpp"
#include "Movie.hpp"

// Maybe include some data structures here
using namespace std;
int INF = std::numeric_limits<int>::max();
/**
 * ActorGraph class builds the graph and applies different operations to it.
 */
class ActorGraph {
  protected:
  public:
    unordered_map<string, Actor*> actors;
    unordered_map<string, Movie*> movies;
    /** Constuctor of the Actor graph
     */
    ActorGraph(void);

    /** Destructor of the Actor graph
     */
    ~ActorGraph();

    /** Only run first and second level BFS from source. */
    void levelBFS(Actor* source, unordered_set<Actor*>& firstLevel,
                  unordered_set<Actor*>& secondLevel);
    unordered_map<string, Actor*> getActors() { return actors; }
    unordered_map<string, Movie*> getMovies() { return movies; }

    /** Builds graph.*/
    void buildGraph(string actor_name, string movie_title, int year);

    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
     * movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);

    /** BFS traverse the actor graph. */
    void BFS(Actor* source);
    /** Dijkstra to find the shortest path in a weighted graph. */
    void Dijkstra(Actor* source);
};

#endif  // ACTORGRAPH_HPP
