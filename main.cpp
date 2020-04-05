#include <iostream>
#include <vector>
#include "Grid.h"
#include "sudoku_utils.h"

using std::cout;
using std::endl;

volatile bool done = false;
volatile bool gridSolved = false;

int main()
{

    std::vector<std::vector<int>> vec = getGridFromFile();

    Grid grid(vec);

    printGrid(grid.gridVec); //print unfinished grid

    grid.fillSquares(false); //false means first time making squares

    bool valid = checkGrid(grid);
    cout << "Valid: " << valid << endl;

    solveGridBackwards(grid, 8, 8);

    if (gridSolved)
    {
        cout << "Done" << endl;
        printGrid(grid.gridVec);
    }
    else
    {
        //remake grid, try again
        std::vector<std::vector<int>> vec2 = getGridFromFile();
        Grid grid2(vec2);
        grid2.fillSquares(false);

        bool valid = checkGrid(grid);
        cout << "Valid: " << valid << endl;

        //solveGridBackwards(grid2, 8, 8);
    }
}