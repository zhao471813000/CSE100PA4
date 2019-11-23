/**
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */
#include <fstream>
#include <iostream>

#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;
/** Return true if file was loaded sucessfully, false otherwise. Store the
 * actors in the actorpair vector. */
bool loadFromPair(const char* in_filename, vector<string>& actorPair) {
    ifstream infile(in_filename);
    bool header = false;
    while (infile) {
        string s;

        // get the next line
        if (!getline(infile, s)) break;

        if (!header) {
            // skip the header
            header = true;
            continue;
        }
        istringstream ss(s);

        while (ss) {
            string str;
            // get the next string before hitting a tab character and put it in
            // 'str'
            if (!getline(ss, str, '\t')) break;
            actorPair.push_back(str);
        }
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}
/* Main program. */
int main(int argc, char** argv) {
    if (argc != 5) {
        cout << "Wrong input!" << endl;
        return -1;
    }
    char* graph_filename = argv[1];
    char* flag = argv[2];
    char* in_filename = argv[3];
    char* out_filename = argv[4];
    bool use_weighted_edges;

    if (flag == "u") {
        use_weighted_edges = false;
    } else {
        use_weighted_edges = true;
    }
    ActorGraph graph;
    graph.loadFromFile(graph_filename, use_weighted_edges);

    vector<string> actorPair;
    loadFromPair(in_filename, actorPair);

    ofstream outfile;
    outfile.open(out_filename, ios::binary | ios::trunc);
    outfile << "(actor)--[movie#@year]-->(actor)--..." << endl;
    for (int i = 0; i < actorPair.size(); i += 2) {
        string source = actorPair[i + 1];
        string target = actorPair[i];
        // check if two actors are in this graph, if true output an empty line
        if (graph.actors.find(source) == graph.actors.end() |
            graph.actors.find(target) == graph.actors.end()) {
            outfile << endl;
            continue;
        }
        graph.BFS(graph.actors[source]);
        Actor* curr = graph.actors[target];
        // check if there exists a path between two actors
        if (curr->prev_actor == NULL) {
            outfile << endl;
            continue;
        }
        while (curr->prev_actor != NULL) {
            outfile << "(" << curr->name << ")--"
                    << "[" << curr->prev_movie->name << "#@"
                    << curr->prev_movie->year << "]-->";
            curr = curr->prev_actor;
        }
        outfile << "(" << curr->name << ")" << endl;
    }
    outfile.close();

    return 0;
}
