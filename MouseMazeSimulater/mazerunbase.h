#ifndef MAZERUNBASE_H
#define MAZERUNBASE_H

#include "mazeconfig.h"
#include "maze.h"

class MazeRunBase
{
public:
    MazeRunBase();

    MazeRunBase(uint8_t x, uint8_t y);

    virtual ~MazeRunBase();

    void setGoal(uint8_t x, uint8_t y);

    uint8_t leftHand();

    uint8_t adachi();

    void wall_init();

protected:
    Position pos;

    uint8_t gx;
    uint8_t gy;
    uint8_t wall[MAZESIZE_X][MAZESIZE_Y];
    Maze *maze;

};

#endif // MAZERUNBASE_H
