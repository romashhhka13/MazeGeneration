#include "Algorithms.h"

using namespace std;

//������� ���������� ������ ������������ ����� ����� ������, � ������� �� ���������
vector<Cell> ChooseFreeCell(Maze& maze, Cell& curr_cell,
    int height, int width)
{
    vector<Cell> free_cell;
    if (curr_cell.x > 0 && !(maze.cell(curr_cell.x - 1, curr_cell.y).visited)) //��������� ����� ������
        free_cell.push_back(maze.cell(curr_cell.x - 1, curr_cell.y));
    if (curr_cell.x < (width - 1) && !(maze.cell(curr_cell.x + 1, curr_cell.y).visited))
        free_cell.push_back(maze.cell(curr_cell.x + 1, curr_cell.y));
    if (curr_cell.y > 0 && !(maze.cell(curr_cell.x, curr_cell.y - 1).visited))
        free_cell.push_back(maze.cell(curr_cell.x, curr_cell.y - 1));
    if (curr_cell.y < (height - 1) && !(maze.cell(curr_cell.x, curr_cell.y + 1).visited))
        free_cell.push_back(maze.cell(curr_cell.x, curr_cell.y + 1));

    return free_cell;
}

// ��������� ���� ����� ��������� ��������������� ��������
void OpenHorisontalWay(Maze& maze, Cell& curr_cell, Cell& next_cell)
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

// ��������� ���� ����� ��������� ������������� ��������
void OpenVerticalWay(Maze& maze, Cell& curr_cell, Cell& next_cell)
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

void RecursiveBacktracker(Maze& maze)
{
    // ����� ��������� ������, ������ ���������� ����, ����� ������� (0, 0)
    srand(time(NULL));
    int start_x = rand() % maze.width;
    int start_y = rand() % maze.height;

    // ������� ������, ��� ����������
    maze.cell(start_x, start_y).visited = true;

    // �������� ����� - ����. ���������� � ���� ��������� ������.
    stack<Cell> path;
    path.push(maze.cell(start_x, start_y));

    while (!path.empty())
    {
        // ������ ������� ������ �� �����. ���������� ��������� ����� ������ ��
        Cell curr_cell = path.top();
        vector<Cell> free_cell = ChooseFreeCell(maze, curr_cell, maze.height, maze.width);

        if (!free_cell.empty())
        {
            // ����� ��������� ��������� ������ �� ���������
            Cell next_cell = free_cell[rand() % free_cell.size()];

            // ���������� ���� ����� ��������� ��������
            OpenHorisontalWay(maze, curr_cell, next_cell);
            OpenVerticalWay(maze, curr_cell, next_cell);

            // ���������� � ����
            maze.cell(next_cell.x, next_cell.y).visited = true;
            path.push(next_cell);
        }
        else
            // ���� ��������� ����� ����� ������, � ������� �� ���������, �� ����,
            // ������� �� �� �����, ������������ � ����������.
            path.pop();
    }
}
