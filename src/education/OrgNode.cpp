#include "OrgNode.h"

// --------------------------------------------------------
// DFS PRINT
// --------------------------------------------------------
void printOrgDFS(OrgNode* root, int depth)
{
    if (!root) return;

    for (int i = 0; i < depth; i++)
        cout << "   ";

    cout << "- " << root->role;

    if (!root->facultyId.empty())
        cout << " [Faculty ID: " << root->facultyId << "]";

    cout << endl;

    OrgNode* child = root->firstChild;
    while (child != nullptr)
    {
        printOrgDFS(child, depth + 1);
        child = child->nextSibling;
    }
}

// --------------------------------------------------------
// FIND ROLE BY NAME
// --------------------------------------------------------
OrgNode* findRole(OrgNode* root, const string& targetRole)
{
    if (!root) return nullptr;
    if (root->role == targetRole) return root;

    OrgNode* child = root->firstChild;
    while (child != nullptr)
    {
        OrgNode* found = findRole(child, targetRole);
        if (found) return found;
        child = child->nextSibling;
    }
    return nullptr;
}

// --------------------------------------------------------
// ADD NEW ROLE UNDER GIVEN PARENT
// --------------------------------------------------------
bool addRoleToNode(OrgNode* root, const string& parentRole, const string& newRole)
{
    OrgNode* parent = findRole(root, parentRole);
    if (!parent) return false;

    OrgNode* newNode = new OrgNode(newRole);

    if (parent->firstChild == nullptr)
    {
        parent->firstChild = newNode;
        return true;
    }

    OrgNode* curr = parent->firstChild;
    while (curr->nextSibling)
        curr = curr->nextSibling;

    curr->nextSibling = newNode;
    return true;
}

// --------------------------------------------------------
// ASSIGN FACULTY TO ROLE
// --------------------------------------------------------
bool assignFacultyToRole(OrgNode* root, const string& roleName, const string& facultyId)
{
    OrgNode* roleNode = findRole(root, roleName);
    if (!roleNode) return false;

    roleNode->facultyId = facultyId;
    return true;
}

// --------------------------------------------------------
// FREE WHOLE ORGANOGRAM TREE
// --------------------------------------------------------
void freeOrgTree(OrgNode* root)
{
    if (!root) return;

    freeOrgTree(root->firstChild);
    freeOrgTree(root->nextSibling);

    delete root;
}
