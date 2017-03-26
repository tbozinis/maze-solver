#include "Solver.h"
#include <iostream>
using std::cout;

Solver::Solver(int tn, int tm)
{
	n = tn;
	m = tm;
}


Solver::~Solver()
{
	
	//metopo.push();
}

list<Point*> Solver::solve_maze() {
	Point *at;
	at = start;
	set_neihbors(at);
	cout << "started..." << std::endl;
	while (!metopo.empty() && at != dest)
	{
		//cout << at->x << " " << at->y << std::endl;
		//get the neighbor thats "closer" to the destination based on the heuristic function
		Neighbor temp_neighbor = metopo.top();
		metopo.pop();
		at = temp_neighbor.p;


		//set surrounding neighbors
		set_neihbors(temp_neighbor.p);
	}
	list<Point*> ret;
	//check if correct dest
	if (at == dest) 
	{
		ret.push_back(at);
		do
		{
			at = at->parent;
			ret.push_front(at);
		} while (at != start);
		
	}
	cout << "fino..." << std::endl;
	return ret;
}

double Solver::manhatan(int x, int y) {
	return abs(x - dest->x) + abs(y - dest->y);
}

double Solver::euklidia(int x, int y) {
	return sqrt(pow(x - dest->x, 2) + pow(y - dest->y, 2));
}

double Solver::distance(int x, int y, int d) {
	double ret = -1;
	switch (slv_alg)
	{
	case BFS:
		ret = h(x, y);
		break;
	case A_STAR:
		ret = h(x, y) + d;
		break;
	}
	return ret;
}

double Solver::h(int x, int y)
{
	switch (h_f)
	{
	case MANCHATAN:
		return manhatan(x, y);
	case EUKLIDIA:
		return euklidia(x, y);
	default:
		return -1;
	}
}

void Solver::neighboring(Neighbor &temp_neighbor, Point* p, Point* temp_point) {
	if (temp_point != NULL) {
		if (!in_metopo(temp_point) && !temp_point->is_wall) {
			temp_point->parent = p;
			temp_point->d = p->d + 1;
			temp_neighbor.p = temp_point;
			temp_neighbor.distance = distance(temp_point->x, temp_point->y, temp_point->d);
			metopo.push(temp_neighbor);
		}
		
		//is_in_metopo.insert({ temp_point->x + temp_point->y, temp_point});
	}
}

void Solver::set_maze(vector<vector<bool>> temp_maze)
{
	cout << "seting maze" << std::endl;
	maze.clear();
	while (!metopo.empty()) metopo.pop();
	cout << "ola popa" << std::endl;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			int key = i + j*n;
			Point* p = new Point;
			p->is_wall = !temp_maze[i][j];
			p->x = i;
			p->y = j;
			p->parent = NULL;
			maze.insert({ key, p });
		}
	}

	//start init
	for (auto it = maze.begin(); it != maze.end(); ++it) {
		if (!it->second->is_wall) {
			start = it->second;
			break;
		}
	}
	cout << "start: " << start->x << ", " << start->y << std::endl;
	//dest init
	auto it = maze.end();
	it--;
	for (; it != maze.begin(); --it) {
		if (!it->second->is_wall) {
			dest = it->second;
			break;
		}
	}
	cout << "dest: " << dest->x << ", " << dest->y << std::endl;
}

void Solver::set_alg(solving_alg sa)
{
	slv_alg = sa;
}

void Solver::set_heuristic(heuristic_f hf)
{
	h_f = hf;
}

bool Solver::in_metopo(Point* p) {
	//pseudo in metopo
	int key = p->x + p->y*n;
	unordered_map<int, Point*>::const_iterator f = maze.find(key);
	bool r = (f->second->parent != NULL);
	return r;
}

void Solver::set_neihbors(Point* p) {
	Neighbor temp_neighbor;
	Point *temp_point;

	temp_point = get_up(p);
	neighboring(temp_neighbor, p, temp_point);

	temp_point = get_down(p);
	neighboring(temp_neighbor, p, temp_point);

	temp_point = get_left(p);
	neighboring(temp_neighbor, p, temp_point);

	temp_point = get_right(p);
	neighboring(temp_neighbor, p, temp_point);
}

Point* Solver::get_up(Point* p) {
	Point* ret = NULL;
	if (p->y - 1 >= 0) {
		int key = p->x + (p->y - 1)*n;
		unordered_map<int, Point*>::const_iterator f = maze.find(key);
		ret = f->second;
	}
	return ret;
}

Point* Solver::get_down(Point* p) {
	Point* ret = NULL;
	if (p->y + 1 < m) {
		int key = p->x + (p->y + 1)*n;
		unordered_map<int, Point*>::const_iterator f = maze.find(key);
		ret = f->second;
	}
	return ret;
}

Point* Solver::get_left(Point* p) {
	Point* ret = NULL;
	if (p->x - 1 >= 0) {
		int key = p->x - 1 + p->y*n;
		unordered_map<int, Point*>::const_iterator f = maze.find(key);
		ret = f->second;
	}
	return ret;
}

Point* Solver::get_right(Point* p) {
	Point* ret = NULL;
	if (p->x + 1 < n) {
		int key = p->x + 1 + p->y*n;
		unordered_map<int, Point*>::const_iterator f = maze.find(key);
		ret = f->second;
	}
	return ret;
}