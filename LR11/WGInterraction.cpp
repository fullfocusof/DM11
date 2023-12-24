#include "WGInterraction.h"

WGInterraction::WGInterraction()
{

}

void WGInterraction::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

void WGInterraction::Read_g()
{
	adjacencyM.resize(MAXV, vector<int>(MAXV, -1));

	ifstream ifs("data.txt");
	if (ifs.is_open())
	{
		ifs >> verts;
		ifs >> edges;
		while (!ifs.eof())
		{
			int v, u, cost;
			ifs >> v;
			ifs >> u;
			ifs >> cost;
			adjacencyM[v][u] = cost;
			edgesList.push_back(make_pair(v, u));
		}
		cout << "Данные успешно считаны";
	}
	else
	{
		cerr << "Ошибка открытия файла";
	}
	ifs.close();
}

void WGInterraction::Print_g()
{
	for (int i = 1; i <= verts; i++)
	{
		cout << i << " вершина: ";
		vector<int> temp;
		for (int j = 1; j <= verts; j++)
		{
			int cost = adjacencyM[i][j];
			if (cost != -1)
			{
				temp.push_back(j);
				cout << j << " (" << cost << ") ";
			}
		}
		if (temp.empty())
		{
			cout << "<нет смежных вершин>";
		}
		cout << endl;
	}
}

vector<int> WGInterraction::DijkstraShortPath(int start, int end, int& shortWay)
{
	vector<int> result;
	vector<int> shortWays(verts + 1, INT_MAX);
	vector<int> prevVerts(verts + 1, -1);
	vector<bool> visited(verts + 1);

	shortWays[start] = 0;

	for (int i = 1; i <= verts; i++)
	{
		int minVert = -1;
		for (int j = 1; j <= verts; j++)
		{
			if (!visited[j] && (minVert == -1 || shortWays[j] < shortWays[minVert]))
			{
				minVert = j;
			}
		}

		if (shortWays[minVert] == INT_MAX)
		{
			break;
		}

		visited[minVert] = true;

		for (int i = 1; i <= verts; i++)
		{
			int cost = adjacencyM[minVert][i];
			if (cost != -1 && shortWays[minVert] + cost < shortWays[i])
			{
				shortWays[i] = shortWays[minVert] + cost;
				prevVerts[i] = minVert;
			}
		}
	}

	shortWay = shortWays[end];

	int current = end;
	while (current != -1)
	{
		result.push_back(current);
		current = prevVerts[current];
	}
	reverse(result.begin(), result.end());
	
	return result;
}

vector<int> WGInterraction::FloydShortPath(int start, int end, int& shortWay, vector<vector<int>>& shortWays)
{
	vector<int> result;
	vector<vector<int>> prevVerts(verts + 1, vector<int>(verts + 1, -1));

	shortWays.resize(verts + 1, vector<int>(verts + 1, INT_MAX));
	for (int i = 1; i <= verts; i++)
	{
		for (int j = 1; j <= verts; j++)
		{
			if (adjacencyM[i][j] != -1)
			{
				shortWays[i][j] = adjacencyM[i][j];
			}
			if (adjacencyM[i][j] != -1 && i != j)
			{
				prevVerts[i][j] = j;
			}		
		}
	}

	for (int i = 1; i <= verts; i++)
	{
		for (int j = 1; j <= verts; j++)
		{
			for (int k = 1; k <= verts; k++)
			{
				if (shortWays[j][i] != INT_MAX && shortWays[i][k] != INT_MAX && (shortWays[j][i] + shortWays[i][k] < shortWays[j][k]))
				{
					shortWays[j][k] = shortWays[j][i] + shortWays[i][k];
					prevVerts[j][k] = prevVerts[j][i];
				}
			}
		}
	}

	shortWay = shortWays[start][end];

	int current = start;
	result.push_back(current);
	while (current != end)
	{
		if (prevVerts[current][end] == -1)
		{
			break;
		}
		current = prevVerts[current][end];
		result.push_back(current);
	}

	return result;
}

vector<int> WGInterraction::BellmanFordShortPath(int start, int end, int& shortWay)
{
	vector<int> result;
	vector<int> shortWays(verts + 1, INT_MAX);
	vector<int> prevVerts(verts + 1, -1);

	shortWays[start] = 0;

	for (int i = 1; i < verts; i++)
	{
		for (auto& el : edgesList)
		{
			int source = el.first;
			int receiver = el.second;
			int cost = adjacencyM[source][receiver];

			if (shortWays[source] != INT_MAX && shortWays[source] + cost < shortWays[receiver])
			{
				shortWays[receiver] = shortWays[source] + cost;
				prevVerts[receiver] = source;
			}
		}
	}

	for (auto& el : edgesList)
	{
		int source = el.first;
		int receiver = el.second;
		int cost = adjacencyM[source][receiver];

		if (shortWays[source] != INT_MAX && shortWays[source] + cost < shortWays[receiver])
		{
			throw exception("Отрицательынй цикл");
		}
	}

	shortWay = shortWays[end];

	int current = end;
	while (current != -1)
	{
		result.push_back(current);
		current = prevVerts[current];
	}
	reverse(result.begin(), result.end());

	return result;	
}