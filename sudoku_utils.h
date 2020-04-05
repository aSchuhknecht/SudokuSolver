#ifndef UTILS
#define UTILS

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Grid.h"

std::vector<std::vector<int>> getGridFromFile();
void printGrid(std::vector<std::vector<int>> &vec);
bool checkGrid(Grid grid);
void printVector(std::vector<int> vec);
void solveGrid(Grid &grid, int x, int y);
void solveGridBackwards(Grid &grid, int x, int y);

#endif