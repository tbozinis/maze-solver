#pragma once

#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <list>

using std::unordered_map;
using std::priority_queue;
using std::vector;
using std::list;

struct Point {
	int x, y;
	bool is_wall;
	Point* parent;
	int d;
};

struct Neighbor{
	Point *p;
	double distance;
	bool operator<(const Neighbor & d) const {
		return distance < d.distance;
	}
};

enum solving_alg
{
	BFS,
	A_STAR
};

enum heuristic_f {
	MANCHATAN,
	EUKLIDIA
};

class Solver
{
private:
	//vector<vector<bool>> maze;
	unordered_map<int, Point*> maze;
	int n, m;	//maze mounds
	Point *start, *dest;;	//starting and ending/destination/goal point
	priority_queue<Neighbor> metopo;
	//unordered_map<int, Point*> is_in_metopo;
	solving_alg slv_alg;
	heuristic_f h_f;

	double distance(int, int, int);
	double h(int, int);
	double manhatan(int, int);
	double euklidia(int, int);
	bool in_metopo(Point*);
	void set_neihbors(Point*);

	Point* get_up(Point*);
	Point* get_down(Point*);
	Point* get_left(Point*);
	Point* get_right(Point*);
	void neighboring(Neighbor &temp_neighbor, Point* , Point*);

public:
	void set_maze(vector<vector<bool>>);
	void set_alg(solving_alg);
	void set_heuristic(heuristic_f);
	list<Point*> solve_maze();
	Solver(int, int);
	~Solver();
};

