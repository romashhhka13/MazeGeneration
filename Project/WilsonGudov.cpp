#include "Algorithms.h"
#include <cstdlib>  // ƒл€ использовани€ функции rand()
#include <ctime>    // ƒл€ инициализации генератора случайных чисел

using namespace std;

void RandomCell(Maze& maze, int& curr_x, int& curr_y)
{
    do {
        curr_x = rand() % maze.width;
        curr_y = rand() % maze.height;
    } while (maze.cell(curr_x, curr_y).visited);
}

vector<pair<int, int>> FindAdjacentCells(Maze& maze, int x, int y)
{
    vector<pair<int, int>> free_cell;
    if (x > 0) //провер€ем левую €чейку
        free_cell.push_back({ x - 1, y });
    if (x < (maze.width - 1))
        free_cell.push_back({ x + 1, y });
    if (y > 0)
        free_cell.push_back({ x, y - 1 });
    if (y < (maze.height - 1))
        free_cell.push_back({ x, y + 1 });

    return free_cell;
}

bool hasCycle(vector<pair<int, int>>& path, int x, int y)
{

    for (int i = 0; i < path.size(); i++) {
        if (path[i].first == x && path[i].second == y) {
            path.erase(path.begin() + i + 1, path.end());
            return true;
        }
    }
    return false;
}

void OpenWall(Maze& maze, pair<int, int>& first_cell, pair<int, int>& second_cell)
{
    int x1 = first_cell.first;
    int x2 = second_cell.first;
    int y1 = first_cell.second;
    int y2 = second_cell.second;

    if (x1 == x2) {
        if (y1 < y2) {
            maze.cell(x1, y1).Bottom = Open;
            maze.cell(x2, y2).Top = Open;
        }
        else {
            maze.cell(x1, y1).Top = Open;
            maze.cell(x2, y2).Bottom = Open;
        }

    }

    if (y1 == y2) {
        if (x1 < x2) {
            maze.cell(x1, y1).Right = Open;
            maze.cell(x2, y2).Left = Open;
        }
        else {
            maze.cell(x1, y1).Left = Open;
            maze.cell(x2, y2).Right = Open;
        }
    }

}

void Wilson(Maze& maze)
{
    srand(time(NULL));
    int unvisitedCells = maze.width * maze.height;

    // ¬ыбираем случайно первую €чейку
    int start_x = rand() % maze.width;
    int start_y = rand() % maze.height;
    int curr_x;
    int curr_y;

    maze.cell(start_x, start_y).visited = true;
    unvisitedCells--;

    // »значально все €чейки помечены как непосещенные
    while (unvisitedCells > 0)
    {
        vector<pair<int, int>> path;
        RandomCell(maze, start_x, start_y);
        path.push_back({ start_x, start_y });
        curr_x = start_x;
        curr_y = start_y;

        while (!maze.cell(curr_x, curr_y).visited)
        {

            vector<pair<int, int>> adjacent_cells = FindAdjacentCells(maze, curr_x, curr_y);
            int rand_cell = rand() % adjacent_cells.size();
            curr_x = adjacent_cells[rand_cell].first;
            curr_y = adjacent_cells[rand_cell].second;

            if (!hasCycle(path, curr_x, curr_y))
                path.push_back({ curr_x, curr_y });

        }

        for (int i = 0; i < path.size(); i++) {
            unvisitedCells--;
            maze.cell(path[i].first, path[i].second).visited = true;
            if (i != path.size() - 1)
                OpenWall(maze, path[i], path[i + 1]);
        }
        unvisitedCells++;

    }

}