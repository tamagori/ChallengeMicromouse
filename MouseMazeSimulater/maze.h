#ifndef MAZE_H
#define MAZE_H

#include "mazeconfig.h"

#include <stdint.h>

struct Position
{
public:
    uint8_t x;
    uint8_t y;
    uint8_t direction;

    void init(){
        x = 0;
        y = 0;
        direction = North;
    }

    void update(uint8_t act)
    {
        uint8_t next = (direction + act) % 4;

        direction = next;

//        方向
//        North : 0
//        West  : 1
//        South : 2
//        East  : 3

//        マウスの向き
//        Front : 0
//        Left  : 1
//        Rear  : 2
//        Right : 3

        if ( direction == North ){
            y++;
        } else if ( direction == West ){
            x--;
        } else if ( direction == South ){
            y--;
        } else {    /* East */
            x++;
        }
    }

};

class Maze
{
public:
    Maze();

    ~Maze();

    uint8_t leftHands(Position *pos, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

    uint8_t get_nextdir(Position *pos, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

    uint8_t map[MAZESIZE_X][MAZESIZE_Y];

private:

    void init_map(uint8_t x, uint8_t y);

    void make_map(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

#if 0
    bool is_unknown(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);
#endif

    int is_unknown(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

    uint8_t get_priority(uint8_t x, uint8_t y, uint8_t dir, uint8_t pos_dir, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);
};

#endif // MAZE_H
