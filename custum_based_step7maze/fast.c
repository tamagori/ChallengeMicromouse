
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"
#include "glob_var.h"
#include "run.h"
#include "interface.h"
#include "sci.h"
#include "mathf.h"

extern int get_nextdir(int x, int y, int mask, t_direction *dir);
extern wait_ms(int wtime);

void fast_run(int x, int y)
{
//引数の座標x,yに向かって最短走行する

	t_direction glob_nextdir;
	int straight_count=0;

	//現在の向きから、次に行くべき方向へ向く
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
	{
		case front:
			straight_count++;			//前向きだった場合は直線を走る距離を伸ばす
			break;
		
		case right:					//右に向く
			turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//右に曲がって
			straight_count = 1;
			break;
		
		case left:					//左に向く
			turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//左に曲がって
			straight_count = 1;
			break;
		
		case rear:					//後ろに向く
			turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//左に曲がって
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;	//自分の向きを更新


	//向いた方向によって自分の座標を更新する
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//北を向いた時はY座標を増やす
			break;
			
		case east:
			mypos.x++;	//東を向いた時はX座標を増やす
			break;
			
		case south:
			mypos.y--;	//南を向いた時はY座標を減らす
			break;
		
		case west:
			mypos.x--;	//西を向いたときはX座標を減らす
			break;

	}


	
	while((mypos.x != x) || (mypos.y != y)){			//ゴールするまで繰り返す


		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
		{
			case front:					//直線をまとめて走るようにする
				straight_count++;
				break;
			
			case right:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//右に曲がって
				straight_count = 1;			//走る直線の距離をリセット
				break;
			
			case left:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//左に曲がって
				straight_count = 1;			//走る直線の距離をリセット
				break;
			
			case rear:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//左に曲がって
				straight_count = 1;			//走る直線の距離をリセット
				break;
		}
	
		mypos.dir = glob_nextdir;	//自分の向きを修正
		
		//向いた方向によって自分の座標を更新する
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//北を向いた時はY座標を増やす
				break;
				
			case east:
				mypos.x++;	//東を向いた時はX座標を増やす
				break;
				
			case south:
				mypos.y--;	//南を向いた時はY座標を減らす
				break;
			
			case west:
				mypos.x--;	//西を向いたときはX座標を減らす
				break;

		}
	}
	straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
}

void xyrad_run(int x, int y)
{
//引数の座標x,yに向かって最短走行する

	t_direction glob_nextdir;
	pos goal_pos;/*最終地点*/
	pos line[18];/*目標軌道 ← 目標点はこの軌道上のどこかに設定する*/
	int i;/*line の要素No*/
	char first_flg = 0;
	float x_def,y_def,l_def;
	float least_def;
	char least_flg;
	char st = 0;
	
	/*グローバル変数の初期化*/
	target_pos.x = 0;/*初期値*/
	target_pos.y = 0;/*初期値*/
	near_pos.x = 0;/*初期値*/
	near_pos.y = 0;/*初期値*/
	now_pos.x = 0;/*初期値*/
	now_pos.y = 0;/*初期値*/
	old_pos.x = 0;
	old_pos.y = 0;
	radian = 0;
	ang_target = 0; /*目標角度*/
	ang_def = 0; /*目標角度と現在角度との角度差*/
	old_len_def = 0;
	old_ang_def = 0;
	
	/*auto変数の初期化*/
	goal_pos.x = x*SECTION;/*X軸ゴール座標[mm]*/
	goal_pos.y = y*SECTION;/*Y軸ゴール座標[mm]*/
	
	/*軌道の初期化*/
	for(i=0;i<18;i++)
	{
		line[i].x = 0;
		line[i].y = 0;
	}
	
	/*割り込み処理内のモード選択*/
	run_mode = XYRAD_RUN;
	
	/*ゴールまで繰り返す*/
	while((goal_pos.x != near_pos.x) && (goal_pos.y != near_pos.y)){	

		(void)get_nextdir(x,y,MASK_SECOND,&glob_nextdir);	//東西南北の情報だけ欲しい
		
		mypos.dir = glob_nextdir;	//自分の向きを修正
		
		//向いた方向によって自分の座標を更新する
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//北を向いた時はY座標を増やす
				for(i = 0;i<9;i++)
				{
					/*X軸変化なし*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x;
					/*Y軸+方向*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y + 10;
				}
				break;
				
			case east:
				mypos.x++;	//東を向いた時はX座標を増やす
				for(i = 0;i<9;i++)
				{
					/*X軸+方向*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x + 10;
					/*Y軸変化なし*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y;
				}
				break;
				
			case south:
				mypos.y--;	//南を向いた時はY座標を減らす
				for(i = 0;i<9;i++)
				{
					/*X軸変化なし*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x;
					/*Y軸-方向*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y - 10;
				}
				break;
			
			case west:
				mypos.x--;	//西を向いたときはX座標を減らす
				for(i = 0;i<9;i++)
				{
					/*X軸-方向*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x - 10;
					/*Y軸変化なし*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y;
				}
				break;
			default:
				/*処理なし*/
				break;
		}
		
		while(first_flg == 1)
		{
			least_flg = 0;
			for(i=st;i<18;i++)
			{
				/*目標軌道上の点で現在位置と最も距離の近い点を探索*/
				x_def = line[i].x - now_pos.x;
				y_def = line[i].y - now_pos.y;
				/*目標点までの距離*/
				l_def = sqrtf(x_def*x_def+y_def*y_def);
				
				if(least_flg == 0)
				{
					least_def = l_def;
					least_flg = 1;
				}
				else if(least_def >= l_def)
				{
					least_def = l_def;
				}
				else
				{
					break;
				}
			}
			st = i-1;
			/*最近傍点の算出*/
			near_pos.x = line[st].x;
			near_pos.y = line[st].y;
			/*上限ガード*/
			if(st+POINT_NUM > 17)
			{
				st = 17 - POINT_NUM;
			}
			/****************OUTPUT*****************/
			target_pos.x = line[st+POINT_NUM].x;
			target_pos.y = line[st+POINT_NUM].y;
			/****************OUTPUT*****************/
			wait_ms(RUN_CAL_CYCLE);/*一定時間待機[ms]*/
			
			if((line[17].x==goal_pos.x)&&(line[17].y==goal_pos.y))
			{
				if(i==17)
				{
					break;
				}
				BEEP();
			}
			else if(i >= 9)
			{
				break;
			}
		}
		first_flg = 1;
		st = 0;
	}
	BEEP();
	while((goal_pos.x != near_pos.x) && (goal_pos.y != near_pos.y))
	{
		
	}
}
