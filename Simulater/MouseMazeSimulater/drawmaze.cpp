#include "drawmaze.h"

DrawMaze::DrawMaze()
{

}

void DrawMaze::init(QGraphicsScene *scene)
{
    /* TODO:マジックナンバーを迷路サイズに応じて変更されるようにする */

    pen.setColor(Qt::lightGray);
    pen.setWidth(1);

    for( int i = 1; i < (MAZESIZE_X+1); i++ ){  /* mazeじゃ正方形であることが前提 */
        QGraphicsTextItem *text_row_on = scene->addText(QString::number(i-1));
        text_row_on->setPos( i * step + 11, 0 );

        QGraphicsTextItem *text_row_under = scene->addText(QString::number(i-1));
        text_row_under->setPos( i * step + 11, step * (MAZESIZE_Y+1) + 21);

        QGraphicsTextItem *text_column_left = scene->addText(QString::number(16-i));
        text_column_left->setPos( 0, i * step + 11 );

        QGraphicsTextItem *text_column_right = scene->addText(QString::number(16-i));
        text_column_right->setPos( step * (MAZESIZE_X+1) + 21, i * step + 11 );

    }

    for ( int i = 1; i <= (MAZESIZE_X+1); i++ ){    /* mazeじゃ正方形であることが前提 */
        scene->addLine(i*step, step, i*step, (MAZESIZE_Y+1)*step, pen);
        scene->addLine(step, i*step, (MAZESIZE_X+1)*step, i*step, pen);
    }

    QGraphicsTextItem *text_goal = scene->addText("G");
    text_goal->setPos( ( GOAL_X + 1 ) * step + 11 , ( MAZESIZE_Y - GOAL_Y ) * step + 11 );

}

void DrawMaze::drawWall(QGraphicsScene *scene, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    scene->clear();
    init(scene);

    pen.setColor(Qt::white);
    pen.setWidth(3);

    for( int x = 0; x < MAZESIZE_X; x++ ){
        for( int y = 0; y < MAZESIZE_Y; y++ ){
            int n = (wall[x][y] & 0x11) >> 0;
            int e = (wall[x][y] & 0x22) >> 1;
            int w = (wall[x][y] & 0x44) >> 2;
            int s = (wall[x][y] & 0x88) >> 3;

            if( n == 0x10 ) scene->addLine( (x+1)*step, (MAZESIZE_Y-y)*step, (x+2)*step, (MAZESIZE_Y-y)*step, pen );


            if( e == 0x10 ) scene->addLine( (x+2)*step, ((MAZESIZE_Y+1)-y)*step, (x+2)*step, (MAZESIZE_Y-y)*step, pen );


            if( w == 0x10 ) scene->addLine( (x+1)*step, ((MAZESIZE_Y+1)-y)*step, (x+1)*step, (MAZESIZE_Y-y)*step, pen );


            if( s == 0x10 ) scene->addLine( (x+1)*step, ((MAZESIZE_Y+1)-y)*step, (x+2)*step, ((MAZESIZE_Y+1)-y)*step, pen );

        }
    }

    pen.setColor(Qt::red);
    pen.setWidth(3);

    for( int x = 0; x < MAZESIZE_X; x++ ){
        for( int y = 0; y < MAZESIZE_Y; y++ ){
            int n = (wall[x][y] & 0x11) >> 0;
            int e = (wall[x][y] & 0x22) >> 1;
            int w = (wall[x][y] & 0x44) >> 2;
            int s = (wall[x][y] & 0x88) >> 3;

            if( n == 0x11 ) scene->addLine( (x+1)*step, (MAZESIZE_Y-y)*step, (x+2)*step, (MAZESIZE_Y-y)*step, pen );


            if( e == 0x11 ) scene->addLine( (x+2)*step, ((MAZESIZE_Y+1)-y)*step, (x+2)*step, (MAZESIZE_Y-y)*step, pen );


            if( w == 0x11 ) scene->addLine( (x+1)*step, ((MAZESIZE_Y+1)-y)*step, (x+1)*step, (MAZESIZE_Y-y)*step, pen );


            if( s == 0x11 ) scene->addLine( (x+1)*step, ((MAZESIZE_Y+1)-y)*step, (x+2)*step, ((MAZESIZE_Y+1)-y)*step, pen );

        }
    }
}

void DrawMaze::drawMachine(QGraphicsScene *scene, uint8_t x, uint8_t y)
{
    /* TODO:dx,dy,box_sizeのマジックナンバーを迷路サイズに応じて変更されるようにする */

    int dx = 7+step;
    int dy = (MAZESIZE_Y+1) * step - 35;
    int box_size = 30;

    QBrush brush(Qt::SolidPattern);
    QPen pen;

    pen.setColor(Qt::cyan);
    brush.setColor(Qt::cyan);

    dx += x * step;
    dy -= y * step;

    scene->addRect(dx, dy, box_size, box_size, pen, brush);
}

void DrawMaze::drawMapStep(QGraphicsScene *scene, uint8_t map[MAZESIZE_X][MAZESIZE_Y])
{
    /* TODO:マジックナンバーを迷路サイズに応じて変更されるようにする */

    for( int x = 0; x < MAZESIZE_X; x++ ){
        for( int y = 0; y < MAZESIZE_Y; y++ ){
            QGraphicsTextItem *text_map_step = scene->addText(QString::number(map[x][y]));
            text_map_step->setPos( ( x + 1 ) * step + 11, ( MAZESIZE_Y - y ) * step + 11 );
        }
    }
}

void DrawMaze::drawSimulate(QGraphicsScene *scene, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    drawWall(scene, wall);
    drawMachine(scene, x, y);
}

void DrawMaze::drawSimulateAdachi(QGraphicsScene *scene, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y], uint8_t map[MAZESIZE_X][MAZESIZE_Y])
{
    drawWall(scene, wall);
    drawMapStep(scene, map);
    drawMachine(scene, x, y);
}
