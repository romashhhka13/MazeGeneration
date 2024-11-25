#include "Algorithms.h"
using namespace std;
void BinaryTree(Maze& maze) {
	srand(time(NULL));
	bool dir;
	for (int y = 0;y < maze.height;y++) {
		for (int x = 0;x < maze.width;x++) {
			dir = rand() % 2;
			if ((dir || x==maze.width-1) && y != 0) {
				maze.cell(x, y).Top = Open;
				maze.cell(x, y - 1).Bottom = Open;
			}
			else if (x != maze.width - 1) {
				maze.cell(x, y).Right = Open;
				maze.cell(x + 1, y).Left = Open;
			};
		};
	};
}
