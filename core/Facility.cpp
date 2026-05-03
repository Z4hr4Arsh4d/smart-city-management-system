#include "Facility.h"
using namespace Facility;

// ======================================================
//                  NODE CONSTRUCTORS
// ======================================================

Node::Node(const string& i, const string& n, const string& s, FACILITY_TYPE t)
    : id(i), name(n), sectorName(s), type(t), nextNode(nullptr), nextType(nullptr) {
}

Adjacency::Adjacency(const string& i, const string& n, const string& s, int w)
    : id(i), name(n), sectorName(s), weight(w), next(nullptr) {
}

Vertex::Vertex(const string& i, const string& n, const string& s)
    : id(i), name(n), sectorName(s), adjHead(nullptr), next(nullptr) {
}

MinHeapNode::MinHeapNode()
    : v(nullptr), dist(2147483647) {
}

MinHeapNode::MinHeapNode(Vertex* vertex, int distance)
    : v(vertex), dist(distance) {
}


// ======================================================
//                  MIN HEAP IMPLEMENTATION
// ======================================================

MinHeap::MinHeap() : arr(nullptr), capacity(0), size(0) {}

MinHeap::~MinHeap() { delete[] arr; }

bool MinHeap::isEmpty() const { return size == 0; }

int MinHeap::getParentIndex(int i) { return (i - 1) / 2; }
int MinHeap::getLeftChildIndex(int i) { return 2 * i + 1; }
int MinHeap::getRightChildIndex(int i) { return 2 * i + 2; }

void MinHeap::swapNodes(int i, int j) {
    MinHeapNode temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void MinHeap::resize() {
    if (capacity == 0) {
        capacity = 8;
        arr = new MinHeapNode[capacity];
        return;
    }
    if (size < capacity) return;

    capacity *= 2;
    MinHeapNode* newArr = new MinHeapNode[capacity];
    for (int i = 0; i < size; i++)
        newArr[i] = arr[i];

    delete[] arr;
    arr = newArr;
}

void MinHeap::heapifyUp(int i) {
    if (i > 0 && arr[getParentIndex(i)].dist > arr[i].dist) {
        swapNodes(getParentIndex(i), i);
        heapifyUp(getParentIndex(i));
    }
}

void MinHeap::heapifyDown(int i) {
    while (true) {
        int left = getLeftChildIndex(i);
        int right = getRightChildIndex(i);

        int smallest = i;
        if (left < size && arr[left].dist < arr[smallest].dist) smallest = left;
        if (right < size && arr[right].dist < arr[smallest].dist) smallest = right;

        if (smallest == i) break;

        swapNodes(i, smallest);
        i = smallest;
    }
}

int MinHeap::findVertex(Vertex* v) {
    for (int i = 0; i < size; i++)
        if (arr[i].v == v)
            return i;
    return -1;
}

void MinHeap::insert(Vertex* v, int dist) {
    resize();
    arr[size] = MinHeapNode(v, dist);
    size++;
    heapifyUp(size - 1);
}

Vertex* MinHeap::getMin(int& dist) {
    if (isEmpty()) { dist = -1; return nullptr; }

    Vertex* ret = arr[0].v;
    dist = arr[0].dist;

    size--;
    if (size > 0) {
        arr[0] = arr[size];
        heapifyDown(0);
    }

    return ret;
}

void MinHeap::decreaseKey(Vertex* v, int newDist) {
    int idx = findVertex(v);
    if (idx == -1) {
        insert(v, newDist);
        return;
    }
    if (newDist >= arr[idx].dist) return;

    arr[idx].dist = newDist;
    heapifyUp(idx);
}


// ======================================================
//                   SUBGRAPH IMPLEMENTATION
// ======================================================

SubGraph::SubGraph() : head(nullptr) {}

SubGraph::~SubGraph() { clear(); }

Vertex* SubGraph::getHead() const { return head; }

Vertex* SubGraph::getVertex(const string& name) const {
    Vertex* curr = head;
    while (curr) {
        if (curr->name == name) return curr;
        curr = curr->next;
    }
    return nullptr;
}

bool SubGraph::searchFacility(const string& name) const {
    return getVertex(name) != nullptr;
}

bool SubGraph::searchNeighbours(const string& f, const string& n) const {
    Vertex* node = getVertex(f);
    if (!node) return false;

    Adjacency* a = node->adjHead;
    while (a) {
        if (a->name == n) return true;
        a = a->next;
    }
    return false;
}

void SubGraph::addFacility(const string& id, const string& name, const string& sectorName) {
    if (searchFacility(name)) {
        cerr << "Facility already exists: " << name << endl;
        return;
    }

    Vertex* newNode = new Vertex(id, name, sectorName);

    if (!head) {
        head = newNode;
        return;
    }

    Vertex* curr = head;
    while (curr->next)
        curr = curr->next;

    curr->next = newNode;
}

void SubGraph::addNeighbour(const string& fName, const string& nName, int weight) {
    Vertex* f = getVertex(fName);
    Vertex* n = getVertex(nName);

    if (!f || !n) return;
    if (searchNeighbours(fName, nName)) return;

    // Add forward edge
    Adjacency* a = new Adjacency(n->id, nName, n->sectorName, weight);
    if (!f->adjHead)
        f->adjHead = a;
    else {
        Adjacency* curr = f->adjHead;
        while (curr->next) curr = curr->next;
        curr->next = a;
    }

    // Add reverse if missing
    if (!searchNeighbours(nName, fName)) {
        Adjacency* rev = new Adjacency(f->id, f->name, f->sectorName, weight);
        if (!n->adjHead)
            n->adjHead = rev;
        else {
            Adjacency* cur = n->adjHead;
            while (cur->next) cur = cur->next;
            cur->next = rev;
        }
    }
}

int SubGraph::size() const {
    int count = 0;
    Vertex* curr = head;
    while (curr) { count++; curr = curr->next; }
    return count;
}

int SubGraph::edgeCount() const {
    int count = 0;
    Vertex* curr = head;
    while (curr) {
        Adjacency* a = curr->adjHead;
        while (a) { count++; a = a->next; }
        curr = curr->next;
    }
    return count / 2;
}

int SubGraph::degree(const string& name) const {
    Vertex* v = getVertex(name);
    if (!v) return -1;

    int count = 0;
    Adjacency* a = v->adjHead;
    while (a) { count++; a = a->next; }
    return count;
}

void SubGraph::print() const {
    Vertex* curr = head;
    while (curr) {
        cout << "Facility: " << curr->name << " -> ";
        Adjacency* a = curr->adjHead;
        while (a) {
            cout << a->name << "(" << a->weight << ") ";
            a = a->next;
        }
        cout << endl;
        curr = curr->next;
    }
}

void SubGraph::clear() {
    Vertex* curr = head;
    while (curr) {
        // delete edges
        Adjacency* a = curr->adjHead;
        while (a) {
            Adjacency* tmp = a;
            a = a->next;
            delete tmp;
        }
        Vertex* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    head = nullptr;
}

void SubGraph::removeNeighbour(const string& fName, const string& nName) {
    Vertex* f = getVertex(fName);
    if (!f) return;

    Adjacency* a = f->adjHead;
    Adjacency* prev = nullptr;

    while (a) {
        if (a->name == nName) {
            if (!prev)
                f->adjHead = a->next;
            else
                prev->next = a->next;

            delete a;
            break;
        }
        prev = a;
        a = a->next;
    }

    // Reverse removal
    Vertex* n = getVertex(nName);
    if (!n) return;

    a = n->adjHead;
    prev = nullptr;

    while (a) {
        if (a->name == fName) {
            if (!prev)
                n->adjHead = a->next;
            else
                prev->next = a->next;

            delete a;
            break;
        }
        prev = a;
        a = a->next;
    }
}

void SubGraph::removeFacility(const string& name) {
    Vertex* target = getVertex(name);
    if (!target) return;

    // delete adjacency list
    Adjacency* a = target->adjHead;
    while (a) {
        Adjacency* tmp = a;
        a = a->next;
        delete tmp;
    }

    // remove from other lists
    Vertex* curr = head;
    while (curr) {
        if (curr->name != name)
            removeNeighbour(curr->name, name);
        curr = curr->next;
    }

    // remove vertex
    if (head && head->name == name) {
        Vertex* tmp = head;
        head = head->next;
        delete tmp;
        return;
    }

    Vertex* prev = head;
    curr = head ? head->next : nullptr;
    while (curr) {
        if (curr->name == name) {
            prev->next = curr->next;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}


// ======================================================
//       DIJKSTRA SHORTEST PATH FOR FACILITY SUBGRAPH
// ======================================================

bool SubGraph::shortestPath(const string& startName, const string& endName,
    string*& path, int& pathLen, int& totalDist)
{
    path = nullptr;
    pathLen = 0;
    totalDist = -1;

    Vertex* start = getVertex(startName);
    Vertex* end = getVertex(endName);
    if (!start || !end) return false;

    int n = size();
    if (n == 0) return false;

    // Build array for index access
    Vertex** arr = new Vertex * [n];
    Vertex* curr = head;
    int idx = 0;

    while (curr) {
        arr[idx++] = curr;
        curr = curr->next;
    }

    int sIdx = -1, eIdx = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == start) sIdx = i;
        if (arr[i] == end) eIdx = i;
    }

    if (sIdx == -1 || eIdx == -1) {
        delete[] arr;
        return false;
    }

    int* dist = new int[n];
    bool* vis = new bool[n];
    int* prev = new int[n];

    for (int i = 0; i < n; i++) {
        dist[i] = 2147483647;
        vis[i] = false;
        prev[i] = -1;
    }

    dist[sIdx] = 0;

    MinHeap heap;
    heap.insert(arr[sIdx], 0);

    while (!heap.isEmpty()) {
        int currD;
        Vertex* u = heap.getMin(currD);
        if (!u) break;

        int uIdx = -1;
        for (int i = 0; i < n; i++)
            if (arr[i] == u) { uIdx = i; break; }

        if (uIdx == -1 || vis[uIdx]) continue;

        vis[uIdx] = true;
        if (uIdx == eIdx) break;

        Adjacency* a = u->adjHead;
        while (a) {
            Vertex* v = getVertex(a->name);
            int vIdx = -1;
            for (int i = 0; i < n; i++)
                if (arr[i] == v) { vIdx = i; break; }

            if (vIdx != -1 && !vis[vIdx]) {
                int newDist = dist[uIdx] + a->weight;
                if (newDist < dist[vIdx]) {
                    dist[vIdx] = newDist;
                    prev[vIdx] = uIdx;
                    heap.decreaseKey(arr[vIdx], newDist);
                }
            }
            a = a->next;
        }
    }

    if (dist[eIdx] == 2147483647) {
        delete[] arr; delete[] dist; delete[] vis; delete[] prev;
        return false;
    }

    totalDist = dist[eIdx];

    // Count nodes in path
    int count = 0;
    int walk = eIdx;
    while (walk != -1) {
        count++;
        walk = prev[walk];
    }

    pathLen = count;
    path = new string[count];

    int pos = count - 1;
    while (eIdx != -1) {
        path[pos--] = arr[eIdx]->name;
        eIdx = prev[eIdx];
    }

    delete[] arr;
    delete[] dist;
    delete[] vis;
    delete[] prev;

    return true;
}


// ======================================================
//         ENUM PRINTING SUPPORT FUNCTION
// ======================================================

ostream& operator<<(ostream& out, FACILITY_TYPE t) {
    switch (t) {
    case EDUCATION:  out << "EDUCATION"; break;
    case MEDICAL:    out << "MEDICAL"; break;
    case PHARMACY:   out << "PHARMACY"; break;
    case TRANSPORT:  out << "TRANSPORT"; break;
    case COMMERCIAL: out << "COMMERCIAL"; break;
    case PUBLIC:     out << "PUBLIC"; break;
    default:         out << "UNKNOWN"; break;
    }
    return out;
}
