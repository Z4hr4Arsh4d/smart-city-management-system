#pragma once
#include <iostream>
#include <string>
#include "Facility.h"
#include "utility/utility.h"
using namespace std;

namespace Sector {

    // Forward declarations
    struct Vertex;
    struct Adjacency;

    // -----------------------------
    // Adjacency List Node
    // -----------------------------
    struct Adjacency {
        Vertex* vertex;
        Adjacency* next;
        int weight;

        Adjacency(Vertex* v, int w);
    };

    // -----------------------------
    // Vertex for Sector Graph
    // -----------------------------
    struct Vertex {
        string name;
        Facility::Node* facilityHead;
        Adjacency* adjHead;
        Vertex* next;

        Vertex(const string& name);
    };

    // -----------------------------
    // MinHeap Node
    // -----------------------------
    struct MinHeapNode {
        Vertex* v;
        int dist;

        MinHeapNode();
        MinHeapNode(Vertex* vertex, int distance);
    };

    // -----------------------------
    // MinHeap for Dijkstra
    // -----------------------------
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

    // -----------------------------------------------------------
    //                  MAIN SECTOR GRAPH CLASS
    // -----------------------------------------------------------
    class Graph {
        Vertex* head;

        string* getNeighbours(const string& data, int& count);
        int* getWeights(const string& data, int& count);
        void clearFacilities(Vertex* v);

    public:
        Graph();
        ~Graph();

        Vertex* getVertex(const string& name) const;
        Vertex* getHead() const;

        bool searchSector(const string& name) const;
        bool searchNeighbours(const string& sectorName, const string& neighbourName) const;

        void addSector(const string& name);
        void addNeighbour(const string& sectorName, const string& neighbourName, int weight);
        void removeNeighbour(const string& sectorName, const string& neighbourName);
        void removeSector(const string& name);

        void loadCSV(const string& filename);
        void print() const;

        int size() const;
        int edgeCount() const;
        int degree(const string& sectorName) const;

        bool shortestPath(const string& startName, const string& endName,
            string*& path, int& pathLen, int& totalDist);

        bool addFacility(const string& sectorName, const string& facilityID,
            const string& facilityName, Facility::FACILITY_TYPE type);

        Facility::Node* getFacilityHead(const string& sectorName) const;
        Facility::Node* getFacilityTypeHead(const string& sectorName,
            Facility::FACILITY_TYPE type);

        bool loadFacilitiesFromCSV(const string& filename, Facility::FACILITY_TYPE type);

        bool removeFacility(const string& sectorName, const string& facilityID,
            Facility::FACILITY_TYPE type);

        Facility::SubGraph* getSubgraph(Facility::FACILITY_TYPE type);

        void clear();

        void printFacilities(const string &sectorName) const;
    };
}
