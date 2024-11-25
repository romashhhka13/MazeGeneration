#include "Algorithms.h"
using namespace std;
void ClearPath(Maze& maze, int x1, int y1, int x2, int y2) {
	if (x1 < x2) {
		maze.cell(x1, y1).Right = Open;
		maze.cell(x2, y2).Left = Open;
	}
	else if (x1 > x2) {
		maze.cell(x1, y1).Left = Open;
		maze.cell(x2, y2).Right = Open;
	}
	else if (y1 < y2) {
		maze.cell(x1, y1).Bottom = Open;
		maze.cell(x2, y2).Top = Open;
	}
	else {
		maze.cell(x1, y1).Top = Open;
		maze.cell(x2, y2).Bottom = Open;
	}
}
void FindAdj(Maze& maze, vector<Cell>& front, int ind) {
	vector<Cell> AvCells;
	if (front[ind].y != 0) {
		if (!maze.cell(front[ind].x, front[ind].y - 1).visited) {
			AvCells.push_back(maze.cell(front[ind].x, front[ind].y - 1));
		}
	}
	if (front[ind].x != 0) {
		if (!maze.cell(front[ind].x - 1, front[ind].y).visited) {
			AvCells.push_back(maze.cell(front[ind].x - 1, front[ind].y));
		}
	}
	if (front[ind].y != maze.height - 1) {
		if (!maze.cell(front[ind].x, front[ind].y + 1).visited) {
			AvCells.push_back(maze.cell(front[ind].x, front[ind].y + 1));
		}
	}
	if (front[ind].x != maze.width - 1) {
		if (!maze.cell(front[ind].x + 1, front[ind].y).visited) {
			AvCells.push_back(maze.cell(front[ind].x + 1, front[ind].y));
		}
	}
	if (AvCells.empty()) {
		front.erase(front.begin() + ind);
	}
	else {
		int i = rand() % AvCells.size();
		int x = AvCells[i].x, y = AvCells[i].y;
		maze.cell(x, y).visited = true;
		front.push_back(maze.cell(x, y));
		ClearPath(maze, x, y, front[ind].x, front[ind].y);
	}
}
void Prime(Maze& maze) {
	srand(time(NULL));
	vector<Cell> front;
	int x = rand() % maze.width, y = rand() % maze.height;
	front.push_back(maze.cell(x, y));
	maze.cell(x, y).visited = true;
	while (!front.empty()) {
		FindAdj(maze, front, rand() % front.size());
	}
}