#include "Algorithms.h"

using namespace std;

//Функция возвращает вектор соседних ячеек около ячейки, в которой мы находимся
vector<Cell> NeighbourCells(Maze& maze, Cell& curr_cell, int height, int width)
{
    vector<Cell> neighbour_cells;
    if (curr_cell.x > 0)
    neighbour_cells.push_back(maze.cell(curr_cell.x - 1, curr_cell.y));
    if (curr_cell.x < (width - 1))
    neighbour_cells.push_back(maze.cell(curr_cell.x + 1, curr_cell.y));
    if (curr_cell.y > 0)
    neighbour_cells.push_back(maze.cell(curr_cell.x, curr_cell.y - 1));
    if (curr_cell.y < (height - 1))
    neighbour_cells.push_back(maze.cell(curr_cell.x, curr_cell.y + 1));

    return neighbour_cells;
}



// Открывает путь между соседними горизонтальными ячейками
void OpenHorisontalWay1(Maze& maze, Cell& curr_cell, Cell& next_cell)
{
    if (next_cell.x != curr_cell.x)
    {
        if (curr_cell.x - next_cell.x > 0)
        {
            maze.cell(curr_cell.x, curr_cell.y).Left = Open;
            maze.cell(next_cell.x, curr_cell.y).Right = Open;
        }
        else
        {
            maze.cell(curr_cell.x, curr_cell.y).Right = Open;
            maze.cell(next_cell.x, curr_cell.y).Left = Open;
        }
    }
}

// Открывает путь между соседними вертикальными ячейками
void OpenVerticalWay1(Maze& maze, Cell& curr_cell, Cell& next_cell)
{
    if (next_cell.y != curr_cell.y)
    {
        if (curr_cell.y - next_cell.y > 0)
        {
            maze.cell(curr_cell.x, curr_cell.y).Top = Open;
            maze.cell(curr_cell.x, next_cell.y).Bottom = Open;
        }
        else
        {
            maze.cell(curr_cell.x, curr_cell.y).Bottom = Open;
            maze.cell(curr_cell.x, next_cell.y).Top = Open;
        }
    }
}

int unvisitedCount(Maze& maze) //Посчитать, сколько клеток не было посещено
{ 
    int count = 0;

    for (int i=0; i<maze.width; ++i)
    {
        for (int j=0; j<maze.height; ++j)
        {
            if (maze.cell(i, j).visited==false)
                count += 1;
        }
            
    }
    return count;
}

void AldousBroder(Maze& maze)
{
    // Выбор рандомной ячейки, откуда начинается путь, можно выбрать (0, 0)
    srand(time(NULL));
    int start_x = rand() % maze.width;
    int start_y = rand() % maze.height;
    Cell curr_cell= maze.cell(start_x, start_y);

    curr_cell.visited = true; // Пометка ячейки, как пройденной

    // Пока существуют свободные ячейки
    while (unvisitedCount(maze)>0)
    {
        vector<Cell> neighbour_cells = NeighbourCells(maze, curr_cell, maze.height, maze.width); // Вектор соседних ячеек
        Cell next_cell = neighbour_cells[rand() % neighbour_cells.size()]; // Выбор случайной ячейки из соседних

        if (maze.cell(next_cell.x, next_cell.y).visited == false) // Если соседняя ячейка не посещена (есть стенка)
        {
            // Открытие пути между текущей и соседней ячейками
            OpenHorisontalWay1(maze, curr_cell, next_cell);
            OpenVerticalWay1(maze, curr_cell, next_cell);

            maze.cell(next_cell.x, next_cell.y).visited = true; //Сосед посещен
        }
        curr_cell = next_cell; // Делаем соседа текущей ячейкой
    }
}
