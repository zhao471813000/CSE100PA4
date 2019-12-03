/*
 * ActorGraph.cpp
 * Author: Kexin Hong A53311871, Dingqian Zhao A53319585
 * Date:   <11/21/2019>
 *
 * This file is meant to exist as a container to read the input file format
 * defined in imdb_2019.tsv.
 */

#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

const int CURRENT_YEAR = 2019;

/** Define a MyComparator to allow for two priorities of the priority queue. */
struct MyComparator {
    bool operator()(pair<int, string> const& p1,
                    pair<int, string> const& p2) const {
        if (p1.first != p2.first) {
            return p1.first > p2.first;
        } else {
            return p1.second < p2.second;
        }
    }
};
typedef priority_queue<pair<int, string>, vector<pair<int, string> >,
                       MyComparator>
    my_min_queue;

/** Constructor of the Actor graph */
ActorGraph::ActorGraph(void) {}

/** Destructor of the Actor graph. */
ActorGraph::~ActorGraph() {
    for (pair<string, Actor*> p : actors) {
        delete p.second;
    }
    for (pair<string, Movie*> p : movies) {
        delete p.second;
    }
}

/**
 * Load the graph from a tab-delimited file of actor->movie relationships.
 *
 * in_filename - input filename
 * use_weighted_edges - if true, compute edge weights as 1 + (2019 -
 * movie_year), otherwise all edge weights will be 1
 *
 * return true if file was loaded sucessfully, false otherwise
 */
bool ActorGraph::loadFromFile(const char* in_filename,
                              bool use_weighted_edges) {
    // Initialize the file stream
    ifstream infile(in_filename);
    bool have_header = false;
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
        // get the next line
        if (!getline(infile, s)) break;
        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }
        istringstream ss(s);
        vector<string> record;
        while (ss) {
            string str;
            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            record.push_back(str);
        }
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int year = stoi(record[2]);
        buildGraph(actor_name, movie_title, year);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}

/** Builds graph. */
void ActorGraph::buildGraph(string actor_name, string movie_title, int year) {
    // add year to movie title in case one movie title in different years
    string movie_title_year = movie_title + to_string(year);
    // update unordered_map actors and movies
    Actor* actor;
    Movie* movie;
    if (actors.find(actor_name) == actors.end()) {
        actor = new Actor(actor_name);
        actors[actor_name] = actor;
    } else {
        actor = actors[actor_name];
    }

    if (movies.find(movie_title_year) == movies.end()) {
        int weight = 1 + (CURRENT_YEAR - year);
        movie = new Movie(movie_title, year, weight);
        movies[movie_title_year] = movie;
    } else {
        movie = movies[movie_title_year];
    }
    // Builds the graph according to unordered_map actors and movies.
    actor->movies.push_back(movie);
    movie->actors.push_back(actor);
}

/** Dijkstra to find the shortest path in a weighted graph. */
void ActorGraph::Dijkstra(Actor* source) {
    my_min_queue pq;
    for (pair<string, Actor*> p : actors) {
        p.second->dist = INF;
        p.second->prev_actor = NULL;
        p.second->prev_movie = NULL;
        p.second->done = false;
    }
    source->dist = 0;
    pq.push(make_pair(source->dist, source->name));
    while (!pq.empty()) {
        Actor* curr = actors[pq.top().second];
        pq.pop();
        if (!curr->done) {
            curr->done = true;
            for (Movie* movie : curr->movies) {
                for (Actor* actor : movie->actors) {
                    int c = curr->dist + movie->weight;
                    if (c < actor->dist) {
                        actor->prev_actor = curr;
                        actor->prev_movie = movie;
                        actor->dist = c;
                        pq.push(make_pair(actor->dist, actor->name));
                    }
                }
            }
        }
    }
}
/** BFS traverse the actor graph. */
void ActorGraph::BFS(Actor* source) {
    // initialize dist and prev for all nodes
    queue<Actor*> toExplore;
    for (pair<string, Actor*> p : actors) {
        p.second->dist = INF;
        p.second->prev_actor = NULL;
        p.second->prev_movie = NULL;
    }
    source->dist = 0;
    toExplore.push(source);

    while (!toExplore.empty()) {
        Actor* next = toExplore.front();
        toExplore.pop();
        for (Movie* movie : next->movies) {
            for (Actor* actor : movie->actors) {
                if (actor->dist == INF) {
                    actor->prev_actor = next;
                    actor->prev_movie = movie;
                    actor->dist = next->dist + 1;
                    toExplore.push(actor);
                }
            }
        }
    }
}
/** Updates the number of edges between actors in the first and second level. */
void ActorGraph::levelBFS(Actor* source, unordered_set<Actor*>& firstLevel,
                          unordered_set<Actor*>& secondLevel) {
    for (pair<string, Actor*> p : actors) {
        p.second->dist = INF;
        p.second->edgeNum.clear();
    }
    source->dist = 0;

    // first level
    for (Movie* movie : source->movies) {
        for (Actor* actor : movie->actors) {
            if (actor->dist > 0) {  // exclude source
                if (actor->edgeNum.find(source) == actor->edgeNum.end()) {
                    actor->edgeNum[source] = 1;
                } else {
                    actor->edgeNum[source] += 1;
                }
                actor->dist = 1;
                firstLevel.insert(actor);
            }
        }
    }
    // second level
    for (Actor* first : firstLevel) {
        for (Movie* movie : first->movies) {
            for (Actor* actor : movie->actors) {
                if (actor->dist >= 1 &&
                    actor->name != first->name) {  // exclude source and itself
                    if (actor->edgeNum.find(first) == actor->edgeNum.end()) {
                        actor->edgeNum[first] = 1;
                    } else {
                        actor->edgeNum[first] += 1;
                    }
                    if (actor->dist > 1) {
                        actor->dist = 2;
                        secondLevel.insert(actor);
                    }
                }
            }
        }
    }
}