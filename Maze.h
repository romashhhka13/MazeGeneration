#pragma once
#include <vector>
#include <iostream>


enum CellState
{
    Close,
    Open
};

struct Cell
{
    int x;
    int y;
    int set;
    bool visited;
    CellState Left;
    CellState Right;
    CellState Top;
    CellState Bottom;
    Cell();
};

class Maze
{
public:
    int width;
    int height;

    void Output();
    Cell& cell(int X, int Y);
    Maze(int Width, int Height);

private:
    std::vector<std::vector<Cell>> cells;
};