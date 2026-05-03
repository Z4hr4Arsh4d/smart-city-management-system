#pragma once
#include <iostream>
#include <string>
#include "../core/utility/utility.h"
using namespace std;

namespace Facility {

    // ======================================================
    // ENUM: Facility Types
    // ======================================================
    enum FACILITY_TYPE { EDUCATION, MEDICAL, PHARMACY, TRANSPORT, COMMERCIAL, PUBLIC };

    // ======================================================
    // Facility Node (stored inside Sector graph)
    // ======================================================
    struct Node {
        string id;
        string name;
        string sectorName;
        FACILITY_TYPE type;

        Node* nextNode;   // Horizontal link (same type)
        Node* nextType;   // Vertical link (different types)

        Node(const string& i, const string& n, const string& s, FACILITY_TYPE t);
    };

    // ======================================================
    // SubGraph Adjacency Node
    // ======================================================
    struct Adjacency {
        string id;
        string name;
        string sectorName;
        int weight;

        Adjacency* next;

        Adjacency(const string& i, const string& n, const string& s, int w);
    };

    // ======================================================
    // SubGraph Vertex (Facility Graph Node)
    // ======================================================
    struct Vertex {
        string id;
        string name;
        string sectorName;

        Adjacency* adjHead;
        Vertex* next;

        Vertex(const string& i, const string& n, const string& s);
    };

    // ======================================================
    // MinHeap Node
    // ======================================================
    struct MinHeapNode {
        Vertex* v;
        int dist;

        MinHeapNode();
        MinHeapNode(Vertex* vertex, int distance);
    };

    // ======================================================
    // MinHeap for Dijkstra on SubGraph
    // ======================================================
    class MinHeap {
        MinHeapNode* arr;
        int capacity;
        int size;

        int getParentIndex(int i);
        int getLeftChildIndex(int i);
        int getRightChildIndex(int i);

        void swapNodes(int i, int j);
        void resize();
        void heapifyUp(int i);
        void heapifyDown(int i);
        int findVertex(Vertex* v);

    public:
        MinHeap();
        ~MinHeap();

        bool isEmpty() const;
        void insert(Vertex* v, int dist);
        Vertex* getMin(int& dist);
        void decreaseKey(Vertex* v, int newDist);
    };

    // ======================================================
    // SubGraph (Graph of specific facility type)
    // ======================================================
    class SubGraph {
        Vertex* head;

    public:
        SubGraph();
        ~SubGraph();

        // Core getters
        Vertex* getHead() const;
        Vertex* getVertex(const string& name) const;
        bool searchFacility(const string& name) const;
        bool searchNeighbours(const string& facility, const string& neighbour) const;

        // Modifiers
        void addFacility(const string& id, const string& name, const string& sectorName);
        void addNeighbour(const string& facilityName, const string& neighbourName, int weight);

        void removeNeighbour(const string& facilityName, const string& neighbourName);
        void removeFacility(const string& name);

        // Analytics
        int size() const;
        int edgeCount() const;
        int degree(const string& name) const;

        // Display
        void print() const;

        // Cleanup
        void clear();

        // Dijkstra shortest path
        bool shortestPath(const string& start, const string& end,
            string*& path, int& pathLen, int& totalDist);
    };

} // namespace Facility

// Pretty-print enum
ostream& operator<<(ostream& out, Facility::FACILITY_TYPE t);
