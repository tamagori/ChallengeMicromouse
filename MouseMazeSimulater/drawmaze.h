#ifndef DRAWMAZE_H
#define DRAWMAZE_H

#include <QtWidgets>
#include "mazeconfig.h"

class DrawMaze
{
public:
    DrawMaze();

    void init(QGraphicsScene *scene);

    void drawWall(QGraphicsScene *scene, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

    void drawMachine(QGraphicsScene *scene, uint8_t x, uint8_t y);

    void drawMapStep(QGraphicsScene *scene, uint8_t map[MAZESIZE_X][MAZESIZE_Y]);

    void drawSimulate(QGraphicsScene *scene, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y]);

    void drawSimulateAdachi(QGraphicsScene *scene, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y], uint8_t map[MAZESIZE_X][MAZESIZE_Y]);

private:
    const int step = 43;

    QPen pen;

};

#endif // DRAWMAZE_H
