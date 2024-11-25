#include "Maze.h"

using namespace std;

Cell::Cell()
{
    Left = Close;
    Right = Close;
    Top = Close;
    Bottom = Close;
}

void Maze::Output()
{
    vector<vector<char>> mas_for_output(height * 2 + 1, (vector<char>(width * 2 + 1, '#')));
    for (auto& cells_row : cells)
    {
        for (auto& cell : cells_row)
        {
            if (cell.Right == Open) {
                mas_for_output[1 + cell.y * 2][1 + cell.x * 2] = ' ';
                mas_for_output[1 + cell.y * 2][2 + cell.x * 2] = ' ';
            }
            else
                mas_for_output[1 + cell.y * 2][1 + cell.x * 2] = ' ';

            if (cell.Bottom == Open)
                mas_for_output[2 + cell.y * 2][1 + cell.x * 2] = ' ';
        }
    }

    for (int row = 0; row < (height * 2 + 1); ++row)
    {
        for (int col = 0; col < (width * 2 + 1); ++col)
            cout << mas_for_output[row][col];
        cout << endl;
    }
}

Cell& Maze::cell(int x, int y)
{
    return cells[y][x];
}

Maze::Maze(int Width, int Height)
{
    width = Width;
    height = Height;

    Cell cell;
    cells.resize(height, (vector<Cell>(width, cell)));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            cells[y][x].y = y;
            cells[y][x].x = x;
            cells[y][x].visited = false;
        }
    }
}

