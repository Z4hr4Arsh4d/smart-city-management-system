#pragma once
#include <string>
#include <iostream>
using namespace std;

// =======================
//  ADJACENCY NODE
// =======================
struct BRAdj {
    string stopID;
    int weight;
    BRAdj* next;

    BRAdj(const string& id, int w)
        : stopID(id), weight(w), next(nullptr) {
    }
};

// =======================
//       GRAPH NODE
// =======================
struct BRNode {
    string stopID;
    BRAdj* adj;
    BRNode* next;

    BRNode(const string& id)
        : stopID(id), adj(nullptr), next(nullptr) {
    }
};

// =======================
//      MAIN CLASS
// =======================
class BusRouteGraph {
private:
    BRNode* head;

public:
    BusRouteGraph();
    ~BusRouteGraph();

    void addStop(const string& stopID);
    void addEdge(const string& a, const string& b, int weight);

    bool shortestPath(const string& start, const string& end,
        string*& path, int& len, int& totalDist);

    void clear();
};
