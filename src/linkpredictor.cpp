/**
 * Predicts whether two actors would act together in the future in an unweighted
 * graph.
 * This part again will have two subparts - the first predicts future
 * collaborations between actors who have collaborated in the past and the
 * second predicts new collaborations between actors.
 *
 * Author: Dingqian Zhao A53319585, Kexin Hong A53311871
 */

#include <algorithm>
#include <fstream>
#include <iostream>

#include "Actor.hpp"
#include "ActorGraph.hpp"
#include "Movie.hpp"

using namespace std;
const int FIXED_PQ_SIZE = 4;  // pq should be fixed-size

/** Define a MyComparator to allow for two priorities of the priority queue.
 * This priority queue is a fixed-lengthed one.*/
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

/** Loads the source actor to a vector from the input filename. */
bool loadSource(const char* in_filename, vector<string>& sourceActor) {
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
            if (!getline(ss, str, '\n')) break;
            sourceActor.push_back(str);
        }
    }
    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}

/** Updates the priority queue of each actor*/
void updatePriority(unordered_set<Actor*> const& firstLevel,
                    unordered_set<Actor*> const& secondLevel,
                    my_min_queue& firstPQ, my_min_queue& secondPQ,
                    Actor* source) {
    int priority;
    for (Actor* actor1 : firstLevel) {
        priority = 0;
        for (Actor* actor2 : firstLevel) {
            if (actor1->name != actor2->name) {
                if (actor1->edgeNum.find(actor2) != actor1->edgeNum.end()) {
                    priority +=
                        actor1->edgeNum[actor2] * actor2->edgeNum[source];
                }
            }
        }
        if (firstPQ.size() < FIXED_PQ_SIZE) {
            firstPQ.push(make_pair(priority, actor1->name));
        } else {
            firstPQ.push(make_pair(priority, actor1->name));
            firstPQ.pop();
        }
    }
    for (Actor* actor1 : secondLevel) {
        priority = 0;
        for (Actor* actor2 : firstLevel) {
            if (actor1->edgeNum.find(actor2) != actor1->edgeNum.end()) {
                priority += actor1->edgeNum[actor2] * actor2->edgeNum[source];
            }
        }
        if (secondPQ.size() < FIXED_PQ_SIZE) {
            secondPQ.push(make_pair(priority, actor1->name));
        } else {
            secondPQ.push(make_pair(priority, actor1->name));
            secondPQ.pop();
        }
    }
}
/** Return a vector of strings from PQ.*/
vector<string> popVector(my_min_queue& pq) {
    vector<string> vec;
    int numActor = pq.size();
    for (int i = 0; i < min(numActor, FIXED_PQ_SIZE); i++) {
        vec.push_back(pq.top().second);
        pq.pop();
    }
    reverse(vec.begin(), vec.end());
    return vec;
}
/** Writes the string in the vector to the output file.*/
void writeActor(ofstream& out, vector<string> const& vec) {
    for (string s : vec) {
        out << s << "\t";
    }
    out << endl;
}
/* Main program. */
int main(int argc, char** argv) {
    if (argc != 5) {
        cout << "Wrong input!" << endl;
        return -1;
    }
    char* graph_filename = argv[1];
    char* actorlist = argv[2];
    char* link_collaborated = argv[3];
    char* link_uncollaborated = argv[4];

    // char* graph_filename = "data/imdb_small_sample.tsv";
    // char* actorlist = "data/test_actors.tsv";
    // char* link_collaborated = "out_link_collaborated.tsv";
    // char* link_uncollaborated = "out_link_uncollaborated.tsv";

    // build actor graph
    ActorGraph graph;
    graph.loadFromFile(graph_filename, false);
    //  read actor into the vector
    vector<string> sourceActor;
    unordered_set<Actor*> firstLevel;
    unordered_set<Actor*> secondLevel;
    loadSource(actorlist, sourceActor);
    ofstream outfile_co;
    ofstream outfile_un;
    outfile_co.open(link_collaborated, ios::binary | ios::trunc);
    outfile_un.open(link_uncollaborated, ios::binary | ios::trunc);
    outfile_co << "Actor1,Actor2,Actor3,Actor4" << endl;
    outfile_un << "Actor1,Actor2,Actor3,Actor4" << endl;
    for (string actorName : sourceActor) {
        firstLevel.clear();
        secondLevel.clear();
        Actor* source = graph.actors[actorName];
        graph.levelBFS(source, firstLevel, secondLevel);
        my_min_queue firstPQ;
        my_min_queue secondPQ;
        updatePriority(firstLevel, secondLevel, firstPQ, secondPQ, source);
        vector<string> collaborated = popVector(firstPQ);
        vector<string> uncollaborated = popVector(secondPQ);
        writeActor(outfile_co, collaborated);
        writeActor(outfile_un, uncollaborated);
    }
    outfile_co.close();
    outfile_un.close();

    return 0;
}
