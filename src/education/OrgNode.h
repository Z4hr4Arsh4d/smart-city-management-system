#pragma once
#include <iostream>
#include <string>
using namespace std;

struct OrgNode
{
    string role;        // Role name: "Principal", "Vice Principal"
    string facultyId;   // Assigned faculty ID ("" if none)

    OrgNode* firstChild;
    OrgNode* nextSibling;

    OrgNode(const string& r = "")
    {
        role = r;
        facultyId = "";
        firstChild = nullptr;
        nextSibling = nullptr;
    }
};

// ---- Function Prototypes (implemented in OrgNode.cpp) ----

// DFS print of organogram
void printOrgDFS(OrgNode* root, int depth = 0);

// Search for a specific role
OrgNode* findRole(OrgNode* root, const string& targetRole);

// Add new role under parent
bool addRoleToNode(OrgNode* root, const string& parentRole, const string& newRole);

// Assign faculty to a role
bool assignFacultyToRole(OrgNode* root, const string& roleName, const string& facultyId);

// Free the entire organogram tree
void freeOrgTree(OrgNode* root);
