#include "Algorithms.h"

using namespace std;

void InitRow(Maze& maze, vector<Cell>& row_set, int y)
{

	int max_set = 0;
	for (int x = 0; x < row_set.size(); x++) {

		if (max_set <= row_set[x].set)
			max_set = row_set[x].set + 1;
		if (row_set[x].Bottom == Close)
			row_set[x].set = -1;
		if (row_set[x].Bottom == Open)
			row_set[x].Top = Open;
		else
			row_set[x].Top = Close;


		// Удаляю в строке все правые стены
		if (x != row_set.size() - 1) {
			row_set[x].Right = Open;
			row_set[x + 1].Left = Open;
		}
		else
			row_set[x].Left = Open;

		row_set[x].Bottom = Close;
		row_set[x].x = x;
		row_set[x].y = y;
	}

	for (int i = 0; i < row_set.size(); i++) {
		if (row_set[i].set == -1)
			row_set[i].set = max_set++;
		else row_set[i].set = row_set[i].set;
	}
}

void FillMaze(Maze& maze, vector<Cell>& row_set, int y)
{
	for (int i = 0; i < maze.width; i++) {
		maze.cell(i, y).Bottom = row_set[i].Bottom;
		maze.cell(i, y).Top = row_set[i].Top;
		maze.cell(i, y).Left = row_set[i].Left;
		maze.cell(i, y).Right = row_set[i].Right;
		maze.cell(i, y).set = row_set[i].set;
	}
}

void CreateBottomWalls(vector<Cell>& row_set, int x, int count)
{
	bool isOpenBottom = false;
	for (int j = 0; j < count; j++) {
		if (rand() % 2) { // Создаём рандомно стены
			row_set[x - count + j].Bottom = Open;
			isOpenBottom = true;
		}
	}
	if (!isOpenBottom)
		row_set[x - count + (rand() % count)].Bottom = Open;
}

void CreateWalls(Maze& maze, vector<Cell>& row_set, int y)
{
	// ШАГ 3. Создайте правые стены для ячеек, двигаясь слева направо, следующим образом.
	// Случайным образом, выбираем добавлять стену или нет.
	for (int i = 1; i < maze.width; i++) {
		if (row_set[i - 1].set != row_set[i].set) {
			if (rand() % 2) {
				row_set[i - 1].Right = Close;
				row_set[i].Left = Close;
			}
			else // Если объединяем в одно множество
				if (i > 3) 
				{
					if (row_set[i - 2].set == row_set[i - 1].set)
						row_set[i].set = row_set[i - 1].set;
					else if (row_set[i - 1].Top == Open)
						row_set[i].set = row_set[i - 1].set;
					else if (row_set[i].Top == Open)
						row_set[i - 1].set = row_set[i].set;
					else
						row_set[i].set = row_set[i - 1].set;
				}
				else 
				{
					if (row_set[i - 1].Top == Open)
						row_set[i].set = row_set[i - 1].set;
					else if (row_set[i].Top == Open)
						row_set[i - 1].set = row_set[i].set;
					else
						row_set[i].set = row_set[i - 1].set;
				}
		}
		else {
			row_set[i - 1].Right = Close;
			row_set[i].Left = Close;
		}
	}

	// ШАГ 4. Создайте нижние стены, двигаясь слева направо
	if (y != maze.height - 1) {
		int count = 1;
		for (int i = 1; i < maze.width; i++) {
			if (row_set[i].set == row_set[i - 1].set)
				count++;

			else {
				CreateBottomWalls(row_set, i, count);
				count = 1;
			}

			if (i == maze.width - 1)
				CreateBottomWalls(row_set, i + 1, count);
		}
	}
}


void CreateWallsAtLastRow(Maze& maze, vector<Cell>& row_set, int y)
{
	// ШАГ 3. Создайте правые стены для ячеек, двигаясь слева направо, следующим образом.
	// Если ячееки принадлежат разным множествам, правая стена не создается, ячееки объединяюся в одно множество
	for (int i = 1; i < maze.width; i++) {
		if (row_set[i - 1].set != row_set[i].set) {
			row_set[i - 1].Right = Open;
			row_set[i].Left = Open;
			row_set[i].set = row_set[i - 1].set;
		}
		else {
			row_set[i - 1].Right = Close;
			row_set[i].Left = Close;
		}
	}

}

void Print(vector<Cell>& row_cell)
{
	for (int i = 0; i < row_cell.size(); i++)
		cout << row_cell[i].set << " ";
	cout << endl;
}

void Eller(Maze& maze)
{
	srand(time(NULL));

	// ШАГ 1. Создаём пустую строку лабиринта
	int y = 0;
	Cell cell;
	vector<Cell> row_set(maze.width, cell);
	for (int i = 0; i < maze.width; i++)
		row_set[i].set = 0;
	InitRow(maze, row_set, y);

	while (y != maze.height - 1) {
		
			CreateWalls(maze, row_set, y);
			FillMaze(maze, row_set, y);
			y++;
			InitRow(maze, row_set, y);
	}
	CreateWallsAtLastRow(maze, row_set, y);
	FillMaze(maze, row_set, y);
}