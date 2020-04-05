#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "sudoku_utils.h"

extern bool done;
extern bool gridSolved;
int stackCount = 0;

std::vector<std::vector<int>> getGridFromFile()
{

    std::vector<std::vector<int>> vec;

    std::ifstream file;
    file.open("grid1.txt");

    if (file.is_open())
    {

        std::string line;
        while (std::getline(file, line, '\n'))
        {

            std::vector<int> tempVec;

            for (int i = 0; i < 9; i++)
            {
                char c = line[i * 2];

                int x = (int)c - 48; //converts to asci, then subtract 48 to get real int
                tempVec.push_back(x);
            }
            vec.push_back(tempVec);
        }
    }
    else
    {
        std::cout << "Error opening text file. \n";
    }

    file.close();

    return vec;
}

void printGrid(std::vector<std::vector<int>> &vec)
{
    std::cout << "\n";
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 9; j++)
        {

            std::cout << "|-----";
        }

        std::cout << "|\n";

        if (i != 9)
        {
            for (int k = 0; k < 9; k++)
            {
                if (vec[i][k] != 0)
                {
                    std::cout << "   " << vec[i][k] << "  ";
                }
                else
                {
                    std::cout << "      ";
                }
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool checkGrid(Grid grid)
{
    for (int i = 0; i < 9; i++)
    {
        std::vector<int> row = grid.gridVec[i];
        std::sort(row.begin(), row.end()); //ith sorted row

        std::vector<int> sq = grid.squares[i].boxes;
        std::sort(sq.begin(), sq.end()); //ith sorted box

        std::vector<int> cols;
        for (int x = 0; x < 9; x++)
        {
            cols.push_back(grid.gridVec[x][i]);
        }
        std::sort(cols.begin(), cols.end()); //ith sorted column

        for (int j = 0; j < 8; j++)
        {
            if ((row[j] == row[j + 1] && row[j] != 0) ||
                (cols[j] == cols[j + 1] && cols[j] != 0) ||
                (sq[j] == sq[j + 1] && sq[j] != 0))
            {
                return false;
            }
        }
    }
    return true;
}

void printVector(std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << "Vector[" << i << "]: " << vec[i] << std::endl;
    }
    std::cout << std::endl;
}

void solveGrid(Grid &grid, int x, int y)
{
    stackCount++;

    if (stackCount == 100000)
    {
        std::cout << "Trying different angle" << std::endl;
        stackCount = 0;
        done = true;
        return;
    }

    //find next non zero box
    if (x == 9)
    {
        done = true;
        gridSolved = true;
        std::cout << "Recursive calls: " << stackCount << std::endl;
        return;
    }

    while (grid.gridVec[x][y] != 0)
    {
        if (y == 8 && x != 8)
        {
            x++;
            y = 0;
        }
        else if (y != 8)
        {
            y++;
        }
        else //y == 8 and x ==8
        {
            done = true;
            gridSolved = true;
            std::cout << "Recursive calls: " << stackCount << std::endl;
            return;
        }
    }

    for (int i = 1; i < 10; i++)
    {
        if (!done)
        {

            grid.gridVec[x][y] = i;
            grid.fillSquares(true);
            bool valid = checkGrid(grid);

            if (valid)
            {
                if (y == 8)
                {
                    solveGrid(grid, x + 1, 0);
                }
                else
                {
                    solveGrid(grid, x, y + 1);
                }
            }
        }
    }
    if (!done)
    {
        grid.gridVec[x][y] = 0; //means not valid, reset
    }
}

void solveGridBackwards(Grid &grid, int x, int y)
{
    stackCount++;

    //find next non zero box
    if (x == -1)
    {
        done = true;
        gridSolved = true;
        std::cout << "Recursive calls: " << stackCount << std::endl;
        return;
    }

    while (grid.gridVec[x][y] != 0)
    {
        if (y == 0 && x != 0)
        {
            x--;
            y = 8;
        }
        else if (y != 0)
        {
            y--;
        }
        else //y == 0 and x == 0
        {
            done = true;
            gridSolved = true;
            std::cout << "Recursive calls: " << stackCount << std::endl;
            return;
        }
    }

    for (int i = 1; i < 10; i++)
    {
        if (!done)
        {

            grid.gridVec[x][y] = i;
            grid.fillSquares(true);
            bool valid = checkGrid(grid);

            if (valid)
            {
                if (y == 0)
                {
                    solveGridBackwards(grid, x - 1, 8);
                }
                else
                {
                    solveGridBackwards(grid, x, y - 1);
                }
            }
        }
    }
    if (!done)
    {
        grid.gridVec[x][y] = 0; //means not valid, reset
    }
}