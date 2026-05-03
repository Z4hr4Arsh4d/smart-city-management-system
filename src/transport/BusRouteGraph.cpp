#include "BusRouteGraph.h"

// =======================
//   CONSTRUCTOR
// =======================
BusRouteGraph::BusRouteGraph() : head(nullptr) {}

BusRouteGraph::~BusRouteGraph() {
    clear();
}

// =======================
// Add Stop if new
// =======================
void BusRouteGraph::addStop(const string& stopID) {
    BRNode* curr = head;
    while (curr) {
        if (curr->stopID == stopID)
            return; // already exists
        curr = curr->next;
    }

    BRNode* n = new BRNode(stopID);
    n->next = head;
    head = n;
}

// =======================
// Add undirected edge a <-> b
// =======================
void BusRouteGraph::addEdge(const string& a, const string& b, int weight) {
    addStop(a);
    addStop(b);

    // find a
    BRNode* A = head;
    while (A && A->stopID != a) A = A->next;

    BRAdj* adj = new BRAdj(b, weight);
    adj->next = A->adj;
    A->adj = adj;

    // reverse
    BRNode* B = head;
    while (B && B->stopID != b) B = B->next;

    BRAdj* adj2 = new BRAdj(a, weight);
    adj2->next = B->adj;
    B->adj = adj2;
}

// =======================
// Count nodes
// =======================
static int countNodes(BRNode* head) {
    int c = 0;
    for (BRNode* n = head; n; n = n->next)
        c++;
    return c;
}

// =======================
// DIJKSTRA WITHOUT VECTORS
// =======================
bool BusRouteGraph::shortestPath(const string& start, const string& end,
    string*& path, int& len, int& totalDist)
{
    path = nullptr;
    len = 0;
    totalDist = -1;

    if (!head) return false;

    int n = countNodes(head);
    if (n == 0) return false;

    // Build node array
    BRNode** nodes = new BRNode * [n];
    int idx = 0;
    for (BRNode* c = head; c; c = c->next)
        nodes[idx++] = c;

    // Find indices
    int sIdx = -1, eIdx = -1;
    for (int i = 0; i < n; i++) {
        if (nodes[i]->stopID == start) sIdx = i;
        if (nodes[i]->stopID == end)   eIdx = i;
    }

    if (sIdx == -1 || eIdx == -1) {
        delete[] nodes;
        return false;
    }

    // Allocate arrays
    int* dist = new int[n];
    bool* vis = new bool[n];
    int* prev = new int[n];

    for (int i = 0; i < n; i++) {
        dist[i] = 999999999;
        vis[i] = false;
        prev[i] = -1;
    }

    dist[sIdx] = 0;

    // Simple Dijkstra (O(n^2) but safe)
    for (int k = 0; k < n; k++) {
        int u = -1;

        // choose minimum unvisited
        for (int i = 0; i < n; i++)
            if (!vis[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        if (u == -1) break;
        vis[u] = true;
        if (u == eIdx) break;

        // relax neighbors
        for (BRAdj* a = nodes[u]->adj; a; a = a->next) {

            int v = -1;

            for (int i = 0; i < n; i++)
                if (nodes[i]->stopID == a->stopID) { v = i; break; }

            if (v != -1 && !vis[v]) {
                int newDist = dist[u] + a->weight;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                }
            }
        }
    }

    if (dist[eIdx] == 999999999) {
        delete[] nodes;
        delete[] dist;
        delete[] vis;
        delete[] prev;
        return false;
    }

    // reconstruct path
    totalDist = dist[eIdx];
    int count = 0;

    for (int v = eIdx; v != -1; v = prev[v]) count++;

    len = count;
    path = new string[count];

    int pos = count - 1;
    for (int v = eIdx; v != -1; v = prev[v])
        path[pos--] = nodes[v]->stopID;

    delete[] nodes;
    delete[] dist;
    delete[] vis;
    delete[] prev;

    return true;
}

// =======================
// FREE MEMORY
// =======================
void BusRouteGraph::clear() {
    BRNode* c = head;
    while (c) {
        BRAdj* a = c->adj;
        while (a) {
            BRAdj* t = a;
            a = a->next;
            delete t;
        }
        BRNode* t = c;
        c = c->next;
        delete t;
    }
    head = nullptr;
}
