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
#include <queue>
#include "Actor.hpp"
#include "Movie.hpp"

using namespace std;

/**
 * Constructor of the Actor graph
 */
ActorGraph::ActorGraph(void) {}

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
            movie = new Movie(movie_title, year);
            movies[movie_title_year] = movie;
        } else {
            movie = movies[movie_title_year];
        }
        // Builds the graph according to unordered_map actors and movies.
        actor->movies.push_back(movie);
        movie->actors.push_back(actor);
    }

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}
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