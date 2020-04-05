#include <iostream>
#include <vector>
#include "sudoku_utils.h"
#include "Grid.h"

Grid::Grid(std::vector<std::vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::vector<int> temp;
        for (int j = 0; j < vec[i].size(); j++)
        {
            temp.push_back(vec[i][j]);
        }
        gridVec.push_back(temp);
    }
}

void Grid::fillSquares(bool replace)
{
    int xoffset = 0;
    int yoffset = 0;

    for (int x = 0; x < 9; x++)
    {
        Square sq;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                sq.boxes.push_back(gridVec[i + xoffset][j + yoffset]);
            }
        }
        if (replace)
        {
            squares.at(x) = sq; //updating vector
        }
        else
        {
            squares.push_back(sq); //if first time making vector
        }

        if (x == 2 || x == 5)
        {
            yoffset = 0;
            xoffset += 3;
        }
        else
        {
            yoffset += 3;
        }
    }
}

void Grid::printSquares()
{
    for (int i = 0; i < 9; i++)
    {
        std::cout << "Square " << i << ": " << std::endl;
        for (int j = 0; j < 9; j++)
        {
            std::cout << j << ": " << squares[i].boxes[j] << std::endl;
        }
    }
    std::cout << std::endl;
}
