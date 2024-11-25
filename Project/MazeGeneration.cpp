#include <iostream>
#include <time.h>
#include <chrono>
#include "Algorithms.h"
#include "Maze.h"

using namespace std;

int GetCorrectNumber(int min, int max)
{
    int x;
    while ((std::cin >> x).fail() || std::cin.peek() != '\n' || x < min || x > max)
    {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please, enter correct number: ";
    }
    return x;
}

void Run(Algorithm a, Maze maze, string author, string name_alg)
{
    auto start = chrono::system_clock::now();
    a(maze);
    auto stop = chrono::system_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(stop - start).count();

    cout << "----------------------------------------------------" << endl;
    cout << "Algorithm: " << name_alg << endl;
    cout << "Author: " << author << endl;
    cout << "Time of maze generation: " << time << " mcs." << endl;
    cout << "----------------------------------------------------" << endl;
    maze.Output();
    cout << endl;
}

int main() {
    /*cout << "Width of maze: ";
    int width = GetCorrectNumber(5, 50);
    cout << "Height of maze: ";
    int height = GetCorrectNumber(5, 50);
    int width = 10;
    int height = 10;*/
    int n = 25;
  
    Maze maze(n, n);
    Run(BinaryTree, maze, "Kononchuk Victor AS-22-05", "BinaryTree");
    Run(Sidewinder, maze, "Saklakova Valeriya AS-22-05", "Sidewinder");
    Run(RecursiveBacktracker, maze, "Ilichev Roman AS-22-05", "RecursiveBacktracker");
    Run(Prime, maze, "Aliev Ali AS-22-05", "Prime");
    Run(AldousBroder, maze, "Gersh Alexey AS-22-05", "AldousBroder");
    Run(Eller, maze, "Mazepa Alexander AS-22-05", "Eller");
    Run(Wilson, maze, "Gudov Nikita AS-22-05", "Wilson");
}

