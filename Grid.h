#ifndef GRID
#define GRID

#include <iostream>
#include <vector>
#include "Square.h"

class Grid
{

public:
    Grid(std::vector<std::vector<int>> vec);

    std::vector<std::vector<int>> gridVec; // full 9x9 grid
    std::vector<Square> squares;           //9 medium squares

    void fillSquares(bool replace);
    void printSquares();
};

#endif