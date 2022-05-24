/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
using namespace cs225;
using namespace std;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();
    private:
        int height;
        int width;
        int end;
        DisjointSets basicSet;
        vector<bool> right;
        vector<bool> down;
};