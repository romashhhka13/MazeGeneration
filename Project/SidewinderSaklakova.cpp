#include "Algorithms.h"

using namespace std;

void Sidewinder(Maze& maze)
{
    srand(time(NULL));
    for (int y = 0; y < maze.height; ++y) {
        int start_x = 0;
        for (int x = 0; x < maze.width; ++x) {

            if (y == 0) { // ”бираем первую строку в лабиринте
                if (x == 0)
                    maze.cell(x, y).Right = Open;
                else if (x < maze.width - 1) {
                    maze.cell(x, y).Right = Open;
                    maze.cell(x + 1, y).Left = Open;
                }
                else
                    maze.cell(x, y).Left = Open;
                continue;
            }

            if (rand() % 2 == 0 && x != maze.width - 1) { // —лучайно выбираем продолжать ли открывать стенки у €чеек справа
                maze.cell(x, y).Right = Open;
                maze.cell(x + 1, y).Left = Open;
            }
            else {
                int rand_x = (rand() % (x - start_x + 1)) + start_x;
                maze.cell(rand_x, y).Top = Open;
                maze.cell(rand_x, y - 1).Bottom = Open;
                start_x = x + 1;
            }
        }
    }
}



