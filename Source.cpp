#include <time.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>

#include "Solver.h"

using namespace std;

vector<vector<bool>> make_maze(int n, int m) {
	srand(time(0));

	const int maze_size_x = n;
	const int maze_size_y = m;
	vector<vector<bool>> maze;
	list<pair<int, int>> drillers;

	maze.resize(maze_size_y);
	for (size_t y = 0;y<maze_size_y;y++)
		maze[y].resize(maze_size_x);

	for (size_t x = 0;x<maze_size_x;x++)
		for (size_t y = 0;y<maze_size_y;y++)
			maze[y][x] = false;

	drillers.push_back(make_pair(maze_size_x / 2, maze_size_y / 2));
	while (drillers.size()>0)
	{
		list < pair < int, int> >::iterator m, _m, temp;
		m = drillers.begin();
		_m = drillers.end();
		while (m != _m)
		{
			bool remove_driller = false;
			switch (rand() % 4)
			{
			case 0:
				(*m).second -= 2;
				if ((*m).second<0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second + 1][(*m).first] = true;
				break;
			case 1:
				(*m).second += 2;
				if ((*m).second >= maze_size_y || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second - 1][(*m).first] = true;
				break;
			case 2:
				(*m).first -= 2;
				if ((*m).first<0 || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first + 1] = true;
				break;
			case 3:
				(*m).first += 2;
				if ((*m).first >= maze_size_x || maze[(*m).second][(*m).first])
				{
					remove_driller = true;
					break;
				}
				maze[(*m).second][(*m).first - 1] = true;
				break;
			}
			if (remove_driller)
				m = drillers.erase(m);
			else
			{
				drillers.push_back(make_pair((*m).first, (*m).second));
				// uncomment the line below to make the maze easier 
				// if (rand()%2) 
				drillers.push_back(make_pair((*m).first, (*m).second));

				maze[(*m).second][(*m).first] = true;
				++m;
			}
		}
	}

	// Done 
	/*for (size_t y = 0;y < maze_size_y;y++) {
		for (size_t x = 0;x < maze_size_x;x++)
		{
			if (maze[y][x])
				printf(" ");
			else
				printf("#");
		}
		printf("\n");
	}*/

	return maze;
}

void printLog(list<Point*> l)
{
	if (!l.empty())
	{
		Point* dest;
		dest = l.back();
		l.pop_back();

		for (; !l.empty();) {
			Point* at = l.front();
			l.pop_front();
			cout << "[" << at->x << ", " << at->y << "]" << " --> ";
		}
		cout << "[" << dest->x << ", " << dest->y << "]" << endl;
	}
	else
	{
		cout << "destination not found..." << endl;
	}
}

int main()
{
	Solver *solver = new Solver(10000, 10000);
	vector<vector<bool>> maze = make_maze(10000, 10000);
	list<Point*> l;

	solver->set_heuristic(heuristic_f::EUKLIDIA);

	solver->set_maze(maze);
	solver->set_alg(solving_alg::BFS);
	l = solver->solve_maze();
	cout << l.size() << endl;
	//printLog(l);

	l.clear();

	solver->set_maze(maze);
	solver->set_alg(solving_alg::A_STAR);
	l = solver->solve_maze();
	cout << l.size() << endl;
	//printLog(l);

	system("pause");
	return 0;
}