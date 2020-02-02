#ifndef MAZECONFIG_H
#define MAZECONFIG_H

#include <stdint.h>

enum Direction :uint8_t
{
    North,
    West,
    South,
    East,
};

enum Action :uint8_t
{
    Front,
    Left,
    Rear,
    Right,
};

/* mazeは正方形あることを前提 */
#define MAZESIZE_X 16
#define MAZESIZE_Y 16

#define GOAL_X 7
#define GOAL_Y 7

#endif // MAZECONFIG_H
