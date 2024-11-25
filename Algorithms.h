#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <tuple>
#include <cmath>
#include <random>
#include <algorithm>
#include "Maze.h"

using Algorithm = void(*)(Maze& maze);

/*Конончук Виктор АС-22-05
АЛГОРИТМ ДВОИЧНОГО ДЕРЕВА*/
void BinaryTree(Maze& maze);

/*Саклакова Валерия АС-22-05
"SIDEWINDER"*/
void Sidewinder(Maze& maze);

/*Ильичев Роман АС-22-05
"RECURSIVE "BACKTRACKER"*/
void RecursiveBacktracker(Maze& maze);

/*Алиев Али АС-22-05
АЛГОРИТМ ПРИМА*/
void Prime(Maze& maze);

/*Герш Алексей АС-22-05
АЛГОРИТМ ОЛДОСА-БРОДЕРА*/
void AldousBroder(Maze& maze);

/*Мазепа Александер АС-22-05
АЛГОРИТМ ЭЛЛЕРА*/
void Eller(Maze& maze);

/*Гудов Никита АС-22-05
АЛГОРИТМ УИЛСОНА*/
void Wilson(Maze& maze);