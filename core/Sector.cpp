#include "Sector.h"

using namespace Sector;

// ==========================================================
//              STRUCT CONSTRUCTORS
// ==========================================================

Adjacency::Adjacency(Vertex* v, int w)
    : vertex(v), weight(w), next(nullptr) {
}

Vertex::Vertex(const string& name)
    : name(name), facilityHead(nullptr), adjHead(nullptr), next(nullptr) {
}

MinHeapNode::MinHeapNode()
    : v(nullptr), dist(2147483647) {
}

MinHeapNode::MinHeapNode(Vertex* vertex, int distance)
    : v(vertex), dist(distance) {
}


// ==========================================================
//                 MIN HEAP IMPLEMENTATION
// ==========================================================

MinHeap::MinHeap() : arr(nullptr), capacity(0), size(0) {}

MinHeap::~MinHeap() { delete[] arr; }

bool MinHeap::isEmpty() const { return size == 0; }

int MinHeap::getParentIndex(int i) { return (i - 1) / 2; }
int MinHeap::getLeftChildIndex(int i) { return 2 * i + 1; }
int MinHeap::getRightChildIndex(int i) { return 2 * i + 2; }

void MinHeap::swapNodes(int i, int j)
{
    MinHeapNode temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void MinHeap::resize()
{
    if (capacity == 0)
    {
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

void MinHeap::heapifyUp(int i)
{
    if (i > 0 && arr[getParentIndex(i)].dist > arr[i].dist)
    {
        swapNodes(getParentIndex(i), i);
        heapifyUp(getParentIndex(i));
    }
}

void MinHeap::heapifyDown(int i)
{
    while (true)
    {
        int left = getLeftChildIndex(i);
        int right = getRightChildIndex(i);
        int smallest = i;

        if (left < size && arr[left].dist < arr[smallest].dist)
            smallest = left;
        if (right < size && arr[right].dist < arr[smallest].dist)
            smallest = right;

        if (smallest == i)
            break;

        swapNodes(i, smallest);
        i = smallest;
    }
}

int MinHeap::findVertex(Vertex* v)
{
    for (int i = 0; i < size; i++)
        if (arr[i].v == v)
            return i;
    return -1;
}

void MinHeap::insert(Vertex* v, int dist)
{
    resize();
    arr[size] = MinHeapNode(v, dist);
    size++;
    heapifyUp(size - 1);
}

Vertex* MinHeap::getMin(int& dist)
{
    if (isEmpty()) { dist = -1; return nullptr; }

    Vertex* retVal = arr[0].v;
    dist = arr[0].dist;

    size--;
    if (size > 0)
    {
        arr[0] = arr[size];
        heapifyDown(0);
    }
    return retVal;
}

void MinHeap::decreaseKey(Vertex* v, int newDist)
{
    int idx = findVertex(v);
    if (idx == -1)
    {
        insert(v, newDist);
        return;
    }
    if (newDist >= arr[idx].dist) return;

    arr[idx].dist = newDist;
    heapifyUp(idx);
}


// ==========================================================
//               GRAPH CLASS IMPLEMENTATION
// ==========================================================

Graph::Graph() : head(nullptr) {}

Graph::~Graph() { clear(); }

Vertex* Graph::getVertex(const string& name) const
{
    Vertex* curr = head;
    while (curr)
    {
        if (curr->name == name)
            return curr;
        curr = curr->next;
    }
    return nullptr;
}

Vertex* Graph::getHead() const { return head; }

bool Graph::searchSector(const string& name) const
{
    return getVertex(name) != nullptr;
}

bool Graph::searchNeighbours(const string& sectorName, const string& neighbourName) const
{
    Vertex* v = getVertex(sectorName);
    if (!v) return false;

    Adjacency* a = v->adjHead;
    while (a)
    {
        if (a->vertex->name == neighbourName)
            return true;
        a = a->next;
    }
    return false;
}

void Graph::addSector(const string& name)
{
    if (searchSector(name))
    {
        cerr << "Sector " << name << " already exists." << endl;
        return;
    }

    Vertex* newNode = new Vertex(name);

    if (!head)
    {
        head = newNode;
        return;
    }

    Vertex* curr = head;
    while (curr->next)
        curr = curr->next;

    curr->next = newNode;
}

void Graph::addNeighbour(const string& sectorName, const string& neighbourName, int weight)
{
    Vertex* s = getVertex(sectorName);
    Vertex* n = getVertex(neighbourName);

    if (!s || !n)
        return;

    if (searchNeighbours(sectorName, neighbourName))
        return;

    Adjacency* newAdj = new Adjacency(n, weight);

    if (!s->adjHead)
        s->adjHead = newAdj;
    else
    {
        Adjacency* a = s->adjHead;
        while (a->next) a = a->next;
        a->next = newAdj;
    }

    // Add reverse edge
    if (!searchNeighbours(neighbourName, sectorName))
    {
        Adjacency* rev = new Adjacency(s, weight);
        if (!n->adjHead)
            n->adjHead = rev;
        else
        {
            Adjacency* r = n->adjHead;
            while (r->next) r = r->next;
            r->next = rev;
        }
    }
}

string* Graph::getNeighbours(const string& data, int& count)
{
    count = 1;
    for (char ch : data) if (ch == ';') count++;

    string* arr = new string[count];
    string temp = "";
    int idx = 0;

    for (char ch : data)
    {
        if (ch == ';')
        {
            arr[idx++] = temp;
            temp = "";
        }
        else temp += ch;
    }
    arr[idx] = temp;
    return arr;
}

int* Graph::getWeights(const string& data, int& count)
{
    count = 1;
    for (char ch : data) if (ch == ';') count++;

    int* arr = new int[count];
    string temp = "";
    int idx = 0;

    for (char ch : data)
    {
        if (ch == ';')
        {
            arr[idx++] = UTIL::stringToInt(temp);
            temp = "";
        }
        else temp += ch;
    }

    arr[idx] = UTIL::stringToInt(temp);
    return arr;
}

void Graph::loadCSV(const string& filename)
{
    int rows, cols;
    string** data = UTIL::CSVParser(filename, rows, cols);
    if (!data) return;

    // Add sectors first
    for (int i = 0; i < rows; i++)
        addSector(data[i][0]);

    // Add neighbours
    for (int i = 0; i < rows; i++)
    {
        string sector = data[i][0];
        int nCount, wCount;

        string* neighbourList = getNeighbours(data[i][1], nCount);
        int* weightList = getWeights(data[i][2], wCount);

        if (nCount != wCount)
        {
            delete[] neighbourList;
            delete[] weightList;
            continue;
        }

        for (int k = 0; k < nCount; k++)
            addNeighbour(sector, neighbourList[k], weightList[k]);

        delete[] neighbourList;
        delete[] weightList;
    }

    UTIL::freeCSV(data, rows);
}

int Graph::size() const
{
    int count = 0;
    Vertex* curr = head;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    return count;
}

int Graph::edgeCount() const
{
    int count = 0;
    Vertex* curr = head;
    while (curr)
    {
        Adjacency* a = curr->adjHead;
        while (a)
        {
            count++;
            a = a->next;
        }
        curr = curr->next;
    }
    return count / 2;
}

int Graph::degree(const string& sectorName) const
{
    Vertex* v = getVertex(sectorName);
    if (!v) return -1;

    int count = 0;
    Adjacency* a = v->adjHead;
    while (a)
    {
        count++;
        a = a->next;
    }
    return count;
}

void Graph::print() const
{
    Vertex* curr = head;
    while (curr)
    {
        cout << "Sector " << curr->name << " -> ";
        Adjacency* a = curr->adjHead;
        while (a)
        {
            cout << "[" << a->vertex->name << " weight:" << a->weight << "] ";
            a = a->next;
        }
        cout << endl;
        curr = curr->next;
    }
}

void Graph::clear()
{
    Vertex* curr = head;
    while (curr)
    {
        Vertex* temp = curr;
        curr = curr->next;

        clearFacilities(temp);

        Adjacency* a = temp->adjHead;
        while (a)
        {
            Adjacency* t = a;
            a = a->next;
            delete t;
        }

        delete temp;
    }
    head = nullptr;
}

void Graph::clearFacilities(Vertex* v)
{
    Facility::Node* row = v->facilityHead;
    while (row)
    {
        Facility::Node* nextRow = row->nextType;

        Facility::Node* c = row;
        while (c)
        {
            Facility::Node* t = c;
            c = c->nextNode;
            delete t;
        }

        row = nextRow;
    }
    v->facilityHead = nullptr;
}

bool Graph::addFacility(const string& sector, const string& fid,
    const string& fname, Facility::FACILITY_TYPE type)
{
    Vertex* v = getVertex(sector);
    if (!v) return false;

    Facility::Node* node = new Facility::Node(fid, fname, sector, type);

    if (!v->facilityHead)
    {
        v->facilityHead = node;
        return true;
    }

    Facility::Node* row = v->facilityHead;
    Facility::Node* prevRow = nullptr;

    while (row && row->type != type)
    {
        prevRow = row;
        row = row->nextType;
    }

    if (!row)
    {
        node->nextType = (prevRow ? prevRow->nextType : v->facilityHead);
        if (!prevRow)
            v->facilityHead = node;
        else
            prevRow->nextType = node;

        return true;
    }

    node->nextNode = row;
    node->nextType = row->nextType;

    if (!prevRow)
        v->facilityHead = node;
    else
        prevRow->nextType = node;

    return true;
}

Facility::Node* Graph::getFacilityHead(const string& sector) const
{
    Vertex* v = getVertex(sector);
    if (!v) return nullptr;
    return v->facilityHead;
}

Facility::Node* Graph::getFacilityTypeHead(const string& sector,
    Facility::FACILITY_TYPE type)
{
    Vertex* v = getVertex(sector);
    if (!v) return nullptr;

    Facility::Node* row = v->facilityHead;
    while (row && row->type != type)
        row = row->nextType;

    return row;
}

bool Graph::removeFacility(const string& sector, const string& id,
    Facility::FACILITY_TYPE type)
{
    Vertex* v = getVertex(sector);
    if (!v) return false;

    Facility::Node* prevRow = nullptr;
    Facility::Node* row = v->facilityHead;

    while (row && row->type != type)
    {
        prevRow = row;
        row = row->nextType;
    }

    if (!row) return false;

    Facility::Node* prev = nullptr;
    Facility::Node* curr = row;

    while (curr && curr->id != id)
    {
        prev = curr;
        curr = curr->nextNode;
    }

    if (!curr) return false;

    if (!prev)
    {
        Facility::Node* newHead = curr->nextNode;
        if (!newHead)
        {
            if (!prevRow)
                v->facilityHead = row->nextType;
            else
                prevRow->nextType = row->nextType;

            delete curr;
        }
        else
        {
            newHead->nextType = row->nextType;
            if (!prevRow)
                v->facilityHead = newHead;
            else
                prevRow->nextType = newHead;

            delete curr;
        }
    }
    else
    {
        prev->nextNode = curr->nextNode;
        delete curr;
    }

    return true;
}

bool Graph::loadFacilitiesFromCSV(const string& filename,
    Facility::FACILITY_TYPE type)
{
    int rows, cols;
    string** data = UTIL::CSVParser(filename, rows, cols);
    if (!data) return false;

    int added = 0;

    for (int i = 0; i < rows; i++)
    {
        string id = data[i][0];
        string name = data[i][1];
        string sector = data[i][2];

        if(UTIL::isNumeric(id) || UTIL::isNumeric(name) || UTIL::isNumeric(sector))
        {
            // if any completely numeric, skip
            continue;
        }

        if (id == "" || name == "" || sector == "") continue;

        if (getVertex(sector))
            if (addFacility(sector, id, name, type))
                added++;
    }

    UTIL::freeCSV(data, rows);
    return added > 0;
}


// ==========================================================
//         DIJKSTRA SHORTEST PATH IMPLEMENTATION
// ==========================================================

bool Graph::shortestPath(const string& startName, const string& endName,
    string*& path, int& pathLen, int& totalDist)
{
    path = nullptr;
    pathLen = 0;
    totalDist = -1;

    Vertex* start = getVertex(startName);
    Vertex* end = getVertex(endName);

    if (!start || !end) return false;

    int n = size();
    Vertex** arr = new Vertex * [n];

    Vertex* curr = head;
    int idx = 0;
    while (curr)
    {
        arr[idx++] = curr;
        curr = curr->next;
    }

    int sIdx = -1, eIdx = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == start) sIdx = i;
        if (arr[i] == end) eIdx = i;
    }

    if (sIdx == -1 || eIdx == -1)
    {
        delete[] arr;
        return false;
    }

    int* dist = new int[n];
    bool* vis = new bool[n];
    int* prev = new int[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = 2147483647;
        vis[i] = false;
        prev[i] = -1;
    }

    dist[sIdx] = 0;

    MinHeap heap;
    heap.insert(arr[sIdx], 0);

    while (!heap.isEmpty())
    {
        int d;
        Vertex* u = heap.getMin(d);
        if (!u) break;

        int uIdx = -1;
        for (int i = 0; i < n; i++)
            if (arr[i] == u) { uIdx = i; break; }

        if (uIdx == -1) continue;
        if (vis[uIdx]) continue;

        vis[uIdx] = true;
        if (uIdx == eIdx) break;

        Adjacency* a = u->adjHead;
        while (a)
        {
            int vIdx = -1;
            for (int i = 0; i < n; i++)
                if (arr[i] == a->vertex) { vIdx = i; break; }

            if (vIdx != -1 && !vis[vIdx])
            {
                int newDist = dist[uIdx] + a->weight;
                if (newDist < dist[vIdx])
                {
                    dist[vIdx] = newDist;
                    prev[vIdx] = uIdx;
                    heap.decreaseKey(arr[vIdx], newDist);
                }
            }
            a = a->next;
        }
    }

    if (dist[eIdx] == 2147483647)
    {
        delete[] arr; delete[] dist; delete[] vis; delete[] prev;
        return false;
    }

    int count = 0;
    int w = eIdx;
    while (w != -1)
    {
        count++;
        w = prev[w];
    }

    pathLen = count;
    path = new string[count];
    totalDist = dist[eIdx];

    int pos = count - 1;
    while (eIdx != -1)
    {
        path[pos--] = arr[eIdx]->name;
        eIdx = prev[eIdx];
    }

    delete[] arr;
    delete[] dist;
    delete[] vis;
    delete[] prev;

    return true;
}


// ==========================================================
//              SUBGRAPH GENERATION
// ==========================================================

Facility::SubGraph* Graph::getSubgraph(Facility::FACILITY_TYPE type)
{
    Facility::SubGraph* g = new Facility::SubGraph();

    Vertex* v = head;
    int count = 0;

    while (v)
    {
        Facility::Node* row = v->facilityHead;

        while (row && row->type != type)
            row = row->nextType;

        for (Facility::Node* c = row; c; c = c->nextNode)
        {
            g->addFacility(c->id, c->name, c->sectorName);
            count++;
        }

        v = v->next;
    }

    if (count <= 1) return g;

    Facility::Node** arr = new Facility::Node * [count];
    int idx = 0;

    v = head;
    while (v)
    {
        Facility::Node* row = v->facilityHead;

        while (row && row->type != type)
            row = row->nextType;

        for (Facility::Node* c = row; c; c = c->nextNode)
            arr[idx++] = c;

        v = v->next;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            Facility::Node* A = arr[i];
            Facility::Node* B = arr[j];

            int w = 0;

            if (A->sectorName != B->sectorName)
            {
                string* path = nullptr;
                int pathLen = 0;
                int totalDist = -1;

                if (shortestPath(A->sectorName, B->sectorName, path, pathLen, totalDist))
                    w = totalDist;
                else
                    w = 2147483647;

                delete[] path;
            }

            g->addNeighbour(A->name, B->name, w);
        }
    }

    delete[] arr;
    return g;
}

void Graph::printFacilities(const string& sectorName) const
{
    Vertex *v = getVertex(sectorName);
    if (v == nullptr)
    {
        cerr << "Sector " << sectorName << " does not exist in the sector network." << endl;
        return;
    }

    Facility::Node *row = v->facilityHead;
    while (row != nullptr)
    {
        cout << "Type " << row->type << ": ";
        Facility::Node *cur = row;
        while (cur != nullptr)
        {
            cout << "ID: " << cur->id << " Name: " << cur->name << " ";
            cur = cur->nextNode;
        }
        cout << endl;
        row = row->nextType;
    }
}
