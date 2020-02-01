#ifndef SIMULATEMAZERUN_H
#define SIMULATEMAZERUN_H

#include "mazerunbase.h"
#include <stdint.h>
#include "drawmaze.h"

class SimulateMazeRun : public MazeRunBase
{
public:
    SimulateMazeRun();

    virtual ~SimulateMazeRun();

    void leftHandSearch(QGraphicsScene *scene);

    void adachiSearch(QGraphicsScene *scene);

    void copyNowMazeData(uint8_t wall_data[MAZESIZE_X][MAZESIZE_Y]);

private:

    void addSimulateWall();

    DrawMaze *draw_maze;

    void msleep(int _time);

    uint8_t simulate_wall[MAZESIZE_X][MAZESIZE_Y];

    void set_wall(int x, int y);

};
#endif // SIMULATEMAZERUN_H
