#include "simulatemazerun.h"

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>

SimulateMazeRun::SimulateMazeRun()
{
    draw_maze = new DrawMaze();
}

SimulateMazeRun::~SimulateMazeRun()
{
    delete draw_maze;
}

void SimulateMazeRun::copyNowMazeData(uint8_t wall_data[MAZESIZE_X][MAZESIZE_Y])
{
    for(int x = 0; x < MAZESIZE_X; x++){
        for(int y = 0; y < MAZESIZE_Y; y++){
            simulate_wall[x][y] = wall_data[x][y];
        }
    }
}

void SimulateMazeRun::leftHandSearch(QGraphicsScene *scene)
{
    uint8_t act = Front;

    wall_init();
    pos.init();

    // 左手法の場合ゴールにたどり着けない可能性があるため、
    // ある一定以上の回数で終わりにする
    int count = 200;

    while(1){

        addSimulateWall();

        draw_maze->drawSimulate(scene, pos.x, pos.y, wall);

        act = leftHand();

        count--;

        msleep( 100 );

        if(gx == pos.x && gy == pos.y) break;

        if(count < 0) break;

    }

    draw_maze->drawSimulate(scene, pos.x, pos.y, wall);
}

void SimulateMazeRun::adachiSearch(QGraphicsScene *scene)
{
    uint8_t act = Front;    /* マウス行動の初期値 */

    wall_init();            /* 探索用迷路情報の初期化 */
    pos.init();             /* マウス位置と方向を初期化(x,y=0かつNorth) */

    int count = 200;

    /* ゴールするまでループ */
    while( (pos.x != gx) || (pos.y != gy) ) /* ゴール判定(falseの時、ゴール) */
    {
        set_wall(pos.x, pos.y);  /* 現在のマウス位置の壁情報をセット(このシミュレーションでは自動的に壁検出は省略される) */

        draw_maze->drawSimulateAdachi(scene, pos.x, pos.y, wall, this->maze->map);     /* 迷路描画とマウス位置描画の更新 */

        act = adachi();

        count--;

        msleep( 100 );

        if(count < 0) break;

    }

    draw_maze->drawSimulate(scene, pos.x, pos.y, wall);

    this->setGoal(0, 0);

    count = 200;

    /* 初期位置までまでループ */
    while( (pos.x != 0) || (pos.y != 0) ) /* ゴール判定(falseの時、ゴール) */
    {
        set_wall(pos.x, pos.y);  /* 現在のマウス位置の壁情報をセット(このシミュレーションでは自動的に壁検出は省略される) */

        draw_maze->drawSimulateAdachi(scene, pos.x, pos.y, wall, this->maze->map);     /* 迷路描画とマウス位置描画の更新 */

        act = adachi();

        count--;

        msleep( 100 );

        if(count < 0) break;

    }

    draw_maze->drawSimulate(scene, pos.x, pos.y, wall);
}

void SimulateMazeRun::set_wall(int x, int y)
{
    //引数の座標x,yに壁情報を書き込む

    wall[x][y] = simulate_wall[x][y];

    uint8_t north = wall[x][y] & 0x01;
    uint8_t east  = wall[x][y] & 0x02;
    uint8_t west  = wall[x][y] & 0x04;
    uint8_t south = wall[x][y] & 0x08;

    if(y < MAZESIZE_Y-1)	//範囲チェック
    {
        wall[x][y+1] |= north << 3;	//反対側から見た壁を書き込み
    }

    if(x < MAZESIZE_X-1)	//範囲チェック
    {
        wall[x+1][y] |= east << 1;	//反対側から見た壁を書き込み
    }

    if(y > 0)	//範囲チェック
    {
        wall[x][y-1] |= south >> 3;	//反対側から見た壁を書き込み
    }

    if(x > 0)	//範囲チェック
    {
        wall[x-1][y] |= west >> 1;	//反対側から見た壁を書き込み
    }

}

void SimulateMazeRun::msleep(int _time)
{
    QEventLoop loop;
    QTimer::singleShot( _time, &loop, SLOT( quit() ) );
    loop.exec();
}

void SimulateMazeRun::addSimulateWall()
{
    wall[pos.x][pos.y] = simulate_wall[pos.x][pos.y];
}
