#pragma once
#include <iostream>
#include <string>	
using namespace std;

struct RouteNode {

	string stopID;
	RouteNode* next;

	RouteNode(const string& id = "") {
		stopID = id;
		next = nullptr;
	}

	

};
