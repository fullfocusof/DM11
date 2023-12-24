#pragma once
#include <iostream>
#include <fstream>

#include <Windows.h>
#include <conio.h>
#include <cmath>

#include <vector>
#include <stack>

#define MAXV 1000

using namespace std;

class WGInterraction
{
public:

	vector<vector<int>> adjacencyM;
	vector<pair<int,int>> edgesList;
	int verts, edges;

	WGInterraction();

	void printQuit();

	void Read_g();
	void Print_g();

	vector<int> DijkstraShortPath(int start, int end, int& shortWay);
	vector<int> FloydShortPath(int start, int end, int& shortWay, vector<vector<int>>& shortWays);
	vector<int> BellmanFordShortPath(int start, int end, int& shortWay);
};