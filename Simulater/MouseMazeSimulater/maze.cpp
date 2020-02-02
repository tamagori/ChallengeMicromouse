#include "maze.h"

Maze::Maze()
{

}

Maze::~Maze()
{

}


uint8_t Maze::leftHands(Position *pos, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    uint8_t act = Rear;
    uint8_t north = wall[pos->x][pos->y] & 0x01;
    uint8_t east = (wall[pos->x][pos->y] & 0x02) >> 1;
    uint8_t west = (wall[pos->x][pos->y] & 0x04) >> 2;
    uint8_t south = (wall[pos->x][pos->y] & 0x08) >> 3;

    if (pos->direction == North){
        if(west == 0){
            act = Left;
        } else if(north == 0){
            act = Front;
        } else if(east == 0){
            act = Right;
        }
    } else if(pos->direction == South) {
        if(east == 0){
            act = Left;
        } else if(south == 0){
            act = Front;
        } else if(west == 0){
            act = Right;
        }
    } else if(pos->direction ==West){
        if(south == 0){
            act = Left;
        } else if(west == 0){
            act = Front;
        } else if(north == 0){
            act = Right;
        }
    } else {    /* East */
        if(north == 0){
            act = Left;
        } else if(east == 0){
            act = Front;
        } else if(south == 0){
            act = Right;
        }
    }

    return act;

}

uint8_t Maze::get_nextdir(Position *pos, uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    //ゴール座標x,yに向かう場合、今どちらに行くべきかを判断する。
    //探索、最短の切り替えのためのmaskを指定、dirは方角を示す
    uint8_t little,priority,tmp_priority;		//最小の値を探すために使用する変数
    uint8_t nextdir = pos->direction;

    make_map(x,y,wall); 		//歩数Map生成
    little = 255;				//最小歩数を255歩(mapがunsigned char型なので)に設定

    priority = 0;				//優先度の初期値は0

    //maskの意味はstatic_parameter.hを参照
    if( (wall[pos->x][pos->y] & 0x01) == 0)			//北に壁がなければ
    {
        tmp_priority = get_priority(pos->x, pos->y + 1, pos->direction, North, wall);	//優先度を算出
        if(map[pos->x][pos->y+1] < little)				//一番歩数が小さい方向を見つける
        {
            little = map[pos->x][pos->y+1];			//ひとまず北が歩数が小さい事にする
            nextdir = North;						//方向を保存
            priority = tmp_priority;				//優先度を保存
        }
        else if(map[pos->x][pos->y+1] == little)			//歩数が同じ場合は優先度から判断する
        {
            if(priority < tmp_priority )				//優先度を評価
            {
                nextdir = North;					//方向を更新
                priority = tmp_priority;			//優先度を保存
            }
        }
    }

    if( ((wall[pos->x][pos->y] & 0x02) >> 1) == 0)			//東に壁がなければ
    {
        tmp_priority = get_priority(pos->x + 1, pos->y, pos->direction, East, wall);	//優先度を算出
        if(map[pos->x + 1][pos->y] < little)				//一番歩数が小さい方向を見つける
        {
            little = map[pos->x+1][pos->y];			//ひとまず東が歩数が小さい事にする
            nextdir = East;						//方向を保存
            priority = tmp_priority;				//優先度を保存
        }
        else if(map[pos->x + 1][pos->y] == little)			//歩数が同じ場合、優先度から判断
        {
            if(priority < tmp_priority)				//優先度を評価
            {
                nextdir = East;					//方向を保存
                priority = tmp_priority;			//優先度を保存
            }
        }
    }

    if( ((wall[pos->x][pos->y] & 0x08) >> 3) == 0)			//南に壁がなければ
    {
        tmp_priority = get_priority(pos->x, pos->y - 1, pos->direction, South, wall);	//優先度を算出
        if(map[pos->x][pos->y - 1] < little)				//一番歩数が小さい方向を見つける
        {
            little = map[pos->x][pos->y-1];			//ひとまず南が歩数が小さい事にする
            nextdir = South;						//方向を保存
            priority = tmp_priority;				//優先度を保存
        }
        else if(map[pos->x][pos->y - 1] == little)			//歩数が同じ場合、優先度で評価
        {
            if(priority < tmp_priority)				//優先度を評価
            {
                nextdir = South;					//方向を保存
                priority = tmp_priority;			//優先度を保存
            }
        }
    }

    if( ((wall[pos->x][pos->y] & 0x04) >> 2) == 0)			//西に壁がなければ
    {
        tmp_priority = get_priority(pos->x - 1, pos->y, pos->direction, West, wall);	//優先度を算出
        if(map[pos->x-1][pos->y] < little)				//一番歩数が小さい方向を見つける
        {
            little = map[pos->x-1][pos->y];			//西が歩数が小さい
            nextdir = West;						//方向を保存
            priority = tmp_priority;				//優先度を保存
        }
        else if(map[pos->x - 1][pos->y] == little)			//歩数が同じ場合、優先度で評価
        {
            if(priority < tmp_priority)              //優先度を評価
            {
                nextdir = West;                    //方向を保存
                priority = tmp_priority;            //優先度を保存
            }
        }
    }

    return ( (uint8_t)( ( 4 + nextdir - pos->direction) % 4 ) );			//どっちに向かうべきかを返す。
                                        //演算の意味はmytyedef.h内のenum宣言から。
}

void Maze::init_map(uint8_t x, uint8_t y)
{
    //迷路の歩数Mapを初期化する。全体を0xff、引数の座標x,yは0で初期化する

    uint8_t i,j;

    for(i = 0; i < MAZESIZE_X; i++)		//迷路の大きさ分ループ(x座標)
    {
        for(j = 0; j < MAZESIZE_Y; j++)	//迷路の大きさ分ループ(y座標)
        {
            map[i][j] = 255;	//すべて255で埋める
        }
    }

    map[x][y] = 0;				//ゴール座標の歩数を０に設定
}

void Maze::make_map(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    //座標x,yをゴールとした歩数Mapを作成する。
    //maskの値(MASK_SEARCH or MASK_SECOND)によって、
    //探索用の歩数Mapを作るか、最短走行の歩数Mapを作るかが切り替わる

    int i,j;
    bool change_flag;			//Map作成終了を見極めるためのフラグ

    init_map(x,y);				//Mapを初期化する

    do
    {
        change_flag = false;				//変更がなかった場合にはループを抜ける
        for(i = 0; i < MAZESIZE_X; i++)			//迷路の大きさ分ループ(x座標)
        {
            for(j = 0; j < MAZESIZE_Y; j++)		//迷路の大きさ分ループ(y座標)
            {
                if(map[i][j] == 255)		//255の場合は次へ
                {
                    continue;
                }

                if(j < MAZESIZE_Y-1)					//範囲チェック
                {
                    if( (wall[i][j] & 0x01) == 0)	//北壁がなければ(maskの意味はstatic_parametersを参照)
                    {
                        if(map[i][j+1] == 255)			//まだ値が入っていなければ
                        {
                            map[i][j+1] = map[i][j] + 1;	//値を代入
                            change_flag = true;		//値が更新されたことを示す
                        }
                    }
                }

                if(i < MAZESIZE_X-1)					//範囲チェック
                {
                    if( ((wall[i][j] & 0x02) >> 1) == 0)		//東壁がなければ
                    {
                        if(map[i+1][j] == 255)			//値が入っていなければ
                        {
                            map[i+1][j] = map[i][j] + 1;	//値を代入
                            change_flag = true;		//値が更新されたことを示す
                        }
                    }
                }

                if(j > 0)						//範囲チェック
                {
                    if( ((wall[i][j] & 0x08) >> 3) == 0)	//南壁がなければ
                    {
                        if(map[i][j-1] == 255)			//値が入っていなければ
                        {
                            map[i][j-1] = map[i][j] + 1;	//値を代入
                            change_flag = true;		//値が更新されたことを示す
                        }
                    }
                }

                if(i > 0)						//範囲チェック
                {
                    if( ((wall[i][j] & 0x04) >> 2) == 0)		//西壁がなければ
                    {
                        if(map[i-1][j] == 255)			//値が入っていなければ
                        {
                            map[i-1][j] = map[i][j] + 1;	//値を代入
                            change_flag = true;		//値が更新されたことを示す
                        }
                    }
                }
            }
        }
    }while(change_flag == true);	//全体を作り終わるまで待つ
}

#if 0
指定された区画が未探索か否かを判断する関数 未探索:true　探索済:false
bool Maze::is_unknown(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    //座標x,yが未探索区間か否かを調べる

    if( wall[x][y] == 0 )
    {			//どこかの壁情報が不明のままであれば
        return true;	//未探索
    }
    else
    {
        return false;	//探索済
    }
}
#endif

int Maze::is_unknown(uint8_t x, uint8_t y, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    //座標x,yで未探索の壁の数を調べる
    int unknownWallCount = 0;
    if(( wall[x][y] & 0x10 ) == 0x00 )
    {
        unknownWallCount++;
    }
    if(( wall[x][y] & 0x20 ) == 0x00 )
    {
        unknownWallCount++;
    }
    if(( wall[x][y] & 0x40 ) == 0x00 )
    {
        unknownWallCount++;
    }
    if(( wall[x][y] & 0x80 ) == 0x00 )
    {
        unknownWallCount++;
    }
    return unknownWallCount;
}

uint8_t Maze::get_priority(uint8_t x, uint8_t y, uint8_t dir, uint8_t pos_dir, uint8_t wall[MAZESIZE_X][MAZESIZE_Y])
{
    //座標x,yと、向いている方角dirから優先度を算出する

    //未探索が一番優先度が高い.(4)
    //それに加え、自分の向きと、行きたい方向から、
    //前(2)横(1)後(0)の優先度を付加する。

    uint8_t priority;	//優先度を記録する変数

    priority = 0;

    if(pos_dir == dir)				//行きたい方向が現在の進行方向と同じ場合
    {
        priority = 2;
    }
    else if( ((4+pos_dir-dir)%4) == 2)		//行きたい方向が現在の進行方向と逆の場合
    {
        priority = 0;
    }
    else						//それ以外(左右どちらか)の場合
    {
        priority = 1;
    }

#if 0
    if(is_unknown(x,y,wall) == true)
    {
        priority += 4;				//未探索の場合優先度をさらに付加
    }
#endif

    priority += (is_unknown(x,y,wall) * 3);  //未探索の壁の数*3をさらに付加

    return priority;				//優先度を返す
}
