#include "CommercialModule.h"

// ---------------------- Resize Mall List ----------------------
void CommercialModule::resizeMallList()
{
    int newCap = mallCapacity * 2;
    ShoppingMall** newList = new ShoppingMall * [newCap];

    for (int i = 0; i < mallCount; ++i)
        newList[i] = malls[i];

    delete[] malls;
    malls = newList;
    mallCapacity = newCap;
}

// ---------------------- Constructor ----------------------
CommercialModule::CommercialModule()
    : mallCount(0), mallCapacity(200)
{
    malls = new ShoppingMall * [mallCapacity];
    mallGraph = nullptr;
}

// ---------------------- Destructor ----------------------
CommercialModule::~CommercialModule()
{
    for (int i = 0; i < mallCount; ++i)
        delete malls[i];

    delete[] malls;
    delete mallGraph;
}

// ---------------------- Getters ----------------------
int CommercialModule::getMallCount() const { return mallCount; }

ShoppingMall* CommercialModule::getMallAt(int index) const
{
    if (index < 0 || index >= mallCount)
        return nullptr;
    return malls[index];
}

// ---------------------- Add Mall ----------------------
void CommercialModule::addMall(ShoppingMall* m)
{
    if (mallCount >= mallCapacity)
        resizeMallList();

    malls[mallCount++] = m;
}

// ---------------------- Attach to Sectors ----------------------
void CommercialModule::attachMallsToSectors(Sector::Graph& graph)
{
    for (int i = 0; i < mallCount; ++i)
    {
        ShoppingMall* m = malls[i];
        graph.addFacility(
            m->getSector(),
            m->getMallID(),
            m->getName(),
            Facility::COMMERCIAL
        );
    }
}

// ---------------------- Build Mall Graph ----------------------
void CommercialModule::buildMallGraph(Sector::Graph& graph)
{
    if (mallGraph)
        delete mallGraph;

    mallGraph = graph.getSubgraph(Facility::COMMERCIAL);

    if (!mallGraph)
        cout << "No malls found in Sector Graph.\n";
    else
        cout << "Mall SubGraph created successfully.\n";
}

// ---------------------- Find Mall by Name ----------------------
ShoppingMall* CommercialModule::findMallByName(const string& name)
{
    for (int i = 0; i < mallCount; ++i)
        if (malls[i]->getName() == name)
            return malls[i];

    return nullptr;
}

// ---------------------- Find Mall by ID ----------------------
ShoppingMall* CommercialModule::findMallByID(const string& id)
{
    for (int i = 0; i < mallCount; ++i)
        if (malls[i]->getMallID() == id)
            return malls[i];

    return nullptr;
}

// ---------------------- Register Mall ----------------------
void CommercialModule::registerMall(const string& id, const string& name, const string& sector)
{
    if (mallCount >= mallCapacity)
    {
        cerr << "Cannot register mall: capacity reached\n";
        return;
    }

    malls[mallCount] = new ShoppingMall(id, name, sector, -1);
    mallCount++;

    cout << "Mall registered successfully\n";
}

// ---------------------- Add Product to Mall ----------------------
void CommercialModule::addProductToMall(const string& mallID,
    const string& productName,
    const string& category)
{
    for (int i = 0; i < mallCount; ++i)
    {
        if (malls[i]->getMallID() == mallID)
        {
            Product p(productName, category);
            malls[i]->addProduct(p);
            cout << "Product added to mall successfully\n";
            return;
        }
    }
    cerr << "Mall not found\n";
}

// ---------------------- Delete Mall By ID ----------------------
void CommercialModule::deleteMallByID(const string& id)
{
    for (int i = 0; i < mallCount; ++i)
    {
        if (malls[i]->getMallID() == id)
        {
            delete malls[i];

            for (int k = i + 1; k < mallCount; ++k)
                malls[k - 1] = malls[k];

            mallCount--;

            cout << "Mall deleted successfully\n";
            return;
        }
    }
    cerr << "Mall not found\n";
}

// ---------------------- Search Product By Name ----------------------
bool CommercialModule::searchProductByName(const string& productName,
    string& mallName,
    Product& result)
{
    for (int i = 0; i < mallCount; ++i)
    {
        if (malls[i]->searchProductByName(productName, result))
        {
            mallName = malls[i]->getName();
            return true;
        }
    }
    return false;
}

// ---------------------- Search Product By Category ----------------------
bool CommercialModule::searchProductByCategory(const string& category,
    string& mallName,
    Product& result)
{
    for (int i = 0; i < mallCount; ++i)
    {
        if (malls[i]->searchProductByCategory(category, result))
        {
            mallName = malls[i]->getName();
            return true;
        }
    }
    return false;
}

// ---------------------- Display All Malls ----------------------
void CommercialModule::displayAllMalls() const
{
    cout << "\n=== All Shopping Malls ===\n";

    for (int i = 0; i < mallCount; ++i)
    {
        cout << "ID: " << malls[i]->getMallID()
            << " | Name: " << malls[i]->getName()
            << " | Sector: " << malls[i]->getSector() << "\n";
    }
    cout << endl;
}

// ---------------------- Display Mall Details ----------------------
void CommercialModule::displayMallDetails(const string& mallName) const
{
    ShoppingMall* m = nullptr;

    for (int i = 0; i < mallCount; ++i)
    {
        if (malls[i]->getName() == mallName)
        {
            m = malls[i];
            break;
        }
    }

    if (!m)
    {
        cout << "Mall not found.\n";
        return;
    }

    cout << "\n=== Mall Details ===\n";
    cout << "ID: " << m->getMallID() << "\n";
    cout << "Name: " << m->getName() << "\n";
    cout << "Sector: " << m->getSector() << "\n";

    m->displayProducts();
}

// ---------------------- Find Nearest Mall ----------------------
ShoppingMall* CommercialModule::findNearestMall(const string& fromMallName)
{
    if (!mallGraph)
    {
        cout << "MallGraph not built.\n";
        return nullptr;
    }

    Facility::Vertex* startV = mallGraph->getVertex(fromMallName);

    if (!startV)
    {
        cout << "Mall not found in subgraph.\n";
        return nullptr;
    }

    string nearestName = "";
    int bestDist = INT_MAX;

    Facility::Vertex* v = mallGraph->getHead();

    while (v)
    {
        if (v->name != fromMallName)
        {
            string* path = nullptr;
            int pathLen = 0;
            int dist = -1;

            bool ok = mallGraph->shortestPath(
                fromMallName, v->name, path, pathLen, dist
            );

            if (ok && dist >= 0 && dist < bestDist)
            {
                bestDist = dist;
                nearestName = v->name;
            }

            delete[] path;
        }

        v = v->next;
    }

    if (nearestName == "")
        return nullptr;

    for (int i = 0; i < mallCount; ++i)
        if (malls[i]->getName() == nearestName)
            return malls[i];

    return nullptr;
}
