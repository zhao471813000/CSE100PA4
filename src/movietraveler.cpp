/**
* For a dataset formatted as "actor/actress<tab>movie<tab>year" where all the
* actors and actresses are connected: Find the optimal route to connected all
* the actors and actresses" By connected, we mean that there exists a path
* between all actors in the equivalent movie graph (similar to that constructed
* in *Part 1); by optimal, we mean that the sum of the edge (movie) weights
* (remember *1 + (2019 - Y) in part 1) should be minimal and the edges should
* connect all the actors in *the dataset; by route, we mean a set of edges, each
* containing the information *of 2 actors/actresses being connected and the
* movie that connects them.

* Author: Dingqian Zhao A53319585, Kexin Hong A53311871
*/

#include <algorithm>
#include <fstream>
#include <iostream>

#include "Actor.hpp"
#include "ActorGraph.cpp"
#include "ActorGraph.hpp"
#include "Edge.hpp"
#include "Movie.hpp"
#include "UF.hpp"

using namespace std;
struct EdgeComparator {
    bool operator()(pair<int, Edge*> const& p1,
                    pair<int, Edge*> const& p2) const {
        if (p1.first != p2.first) {
            return p1.first > p2.first;
        } else {
            return p1.second->movie->name > p2.second->movie->name;
        }
    }
};
typedef priority_queue<pair<int, Edge*>, vector<pair<int, Edge*> >,
                       EdgeComparator>
    edge_priority_queue;

/** Use Kruskal's algorithm to find the minimum spanning tree of the actor
 * graph. */
void kruskalMST(edge_priority_queue& pq, ActorGraph& graph,
                unordered_set<Edge*>& edgeSet) {
    UF uf;
    while (edgeSet.size() < graph.actors.size() - 1) {
        Edge* e = pq.top().second;
        pq.pop();
        Actor* actor1 = e->actor1;
        Actor* actor2 = e->actor2;
        if (!uf.connected(actor1, actor2)) {
            uf.connect(actor1, actor2);
            edgeSet.insert(e);
        }
    }
}

/* Main program. */
int main(int argc, char** argv) {
    char* graph_filename = argv[1];
    char* printpath = argv[2];

    // build actor graph
    ActorGraph graph;
    graph.loadFromFile(graph_filename, true);

    // put edges in pq
    edge_priority_queue edgePQ;
    vector<Edge*> edgeVec;
    for (pair<string, Movie*> p : graph.movies) {
        int size = p.second->actors.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                Edge* e = new Edge(p.second->weight, p.second,
                                   p.second->actors[i], p.second->actors[j]);
                edgePQ.push(make_pair(e->weight, e));
                edgeVec.push_back(e);
            }
        }
    }

    // run kruskal's
    unordered_set<Edge*> edgeSet;
    kruskalMST(edgePQ, graph, edgeSet);

    // open output file to write the MST edges
    ofstream outfile;
    outfile.open(printpath, ios::binary | ios::trunc);

    outfile << "(actor)<--[movie#@year]-->(actor)" << endl;
    int totalWeight = 0;
    for (Edge* edge : edgeSet) {
        totalWeight += edge->weight;
        outfile << "(" << edge->actor1->name << ")<--[" << edge->movie->name
                << "#@" << edge->movie->year << "]-->(" << edge->actor2->name
                << ")" << endl;
    }
    outfile << "#NODE CONNECTED: " << edgeSet.size() + 1 << endl;
    outfile << "#EDGE CHOSEN: " << edgeSet.size() << endl;
    outfile << "TOTAL EDGE WEIGHTS: " << totalWeight << endl;

    outfile.close();
    for (Edge* e : edgeVec) {
        delete e;
    }
    return 0;
}
