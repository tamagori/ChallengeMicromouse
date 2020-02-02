
#include "mazerunbase.h"

MazeRunBase::MazeRunBase()
{
    maze = new Maze();
    pos.init();
    wall_init();
}

MazeRunBase::~MazeRunBase()
{
    delete maze;
}

MazeRunBase::MazeRunBase(uint8_t x, uint8_t y)
{
    gx = x;
    gy = y;
}

void MazeRunBase::setGoal(uint8_t x, uint8_t y)
{
    gx = x;
    gy = y;
}

uint8_t MazeRunBase::leftHand()
{
  uint8_t act = Rear;

  act = maze->leftHands(&pos, wall);
  pos.update(act);

  return act;
}

uint8_t MazeRunBase::adachi()
{
    uint8_t act = Rear;

    act = maze->get_nextdir(&pos, gx, gy, wall);      /* 次動作のマウス方向算出 */
    pos.update( act );                                /* マウス位置(pos.x, pos.y)を更新 */

    return act;
}

void MazeRunBase::wall_init()
{
    for(int x = 0; x< MAZESIZE_X; x++){
        for(int y = 0; y< MAZESIZE_Y; y++){
            wall[x][y] = 0;
            if(y == MAZESIZE_Y-1)
            {
                wall[x][y] |= 0x11; /* 一番北の壁 */
            }
            if(x == MAZESIZE_X-1)
            {
                wall[x][y] |= 0x22; /* 一番東の壁 */
            }
            if(x == 0)
            {
                wall[x][y] |= 0x44; /* 一番西の壁 */
            }
            if(y == 0)
            {
                wall[x][y] |= 0x88; /* 一番南の壁 */
            }
        }
    }
}
