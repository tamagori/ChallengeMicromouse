
#ifndef _PARAMETER

#include "static_parameters.h"　

//物理的なパラメータ
#define TIRE_DIAMETER	(12.95)			                //タイヤの直径	[mm]
#define TIRE_RADIUS	    (TIRE_DIAMETER/2.0)		            //タイヤの半径	[mm]
#define MMPP 		    (TIRE_DIAMETER*PI)/(ENC_RES_MAX)	//エンコーダ1パルスあたりに進む距離[mm](TIRE_DIAMETER*PI)/(ENC_MAX)
#define ENC_RES_MAX	    (1024)
#define ENC_RES_HALF	(512)

#define SLA_STRAIGHT    (10.0)              //スラローム前後の直進  [mm]

#define V_ref		3.8				//モータ制御の基準電圧

//ログ用のパラメータ
#define LOG_CNT		1000				//ログをとる個数。 1mmsで取得しているので、取得時間[s]はこの数の1000分の1

//センサ関連パラメータ
#define WAITLOOP_SLED	180				//LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数

#define REF_SEN_R	1306				//マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	1279				//マウスを迷路中央に置いた時のセンサの値

#define TH_SEN_R	95				//壁があるか否かの閾値	車体を区画の左へ寄せた時のセンサ値(壁あり)
#define TH_SEN_L	48				//壁があるか否かの閾値	車体を区画の右へ寄せた時のセンサ値(壁あり)
#define TH_SEN_FR	70				//壁があるか否かの閾値	
#define TH_SEN_FL	48				//壁があるか否かの閾値

#define CONTH_SEN_R	TH_SEN_R			//制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L			//制御をかけるか否かの閾値
#define CON_WALL_KP	(10.0)				//壁センサによる姿勢制御の比例制御の比例定数 (2/1説明会のときは3.0)

//フィードバックゲインパラメータ
//Pゲイン　最初に調整する	実速度が目標速度を中心として軽く振動する程度に調整
//Iゲイン　最後に調整する	積分値が合うようにする程度。
//Dゲイン　二番目に調整する。	P制御によって発生した振動を抑えられる程度に調整
//車体中心における並進方向速度に関するフィードバックゲイン
#define SPEED_KP	(20.0)				//Pゲイン
#define SPEED_KI	(0.3)				//Iゲイン
#define SPEED_KD	(0.0)				//Dゲイン　
//車体中心における回転方向速度に関するフィードバックゲイン
#define OMEGA_KP	(40.0)				//Pゲイン
#define OMEGA_KI	(0.07)				//Iゲイン
#define OMEGA_KD	(1.0)				//Dゲイン

//走行パラメータ
#define SEARCH_SPEED		(0.3)			//探索走行の速度	[m/s]
#define SEARCH_SLA_SPEED	(0.3)			//探索走行の速度	[m/s]
#define SEARCH_SLA_ANG_SPEED	(15.76)		//探索走行のスラローム角速度      [rad/s]
#define SEARCH_SLA_ANG_ACCEL	(160.0)		//探索走行のスラローム角加速度    [rad/s^2]
#define SEARCH_ACCEL	(SEARCH_SLA_SPEED/((HALF_SECTION+SLA_STRAIGHT)/1000.0/SEARCH_SLA_SPEED))	//探索走行の加速度	[m/s^2]

#define FAST_SPEED		(0.5)				//最短走行の速度	[m/s]

//↓↓↓ スラローム時の速度は以下から選択する ↓↓↓
#define FAST_SLA_SPEED	(0.3)				//最短走行のスラローム速度	[m/s]
#define FAST_SLA_ANG_SPEED		(15.76)		//最短走行のスラローム角速度      [rad/s]
#define FAST_SLA_ANG_ACCEL		(160.0)		//最短走行のスラローム角加速度    [rad/s^2]

//#define FAST_SLA_SPEED	(0.4)				//最短走行のスラローム速度	[m/s]
//#define FAST_SLA_ANG_SPEED		(20.8005)	//最短走行のスラローム角速度      [rad/s]
//#define FAST_SLA_ANG_ACCEL		(283.0)		//最短走行のスラローム角加速度    [rad/s^2]

//#define FAST_SLA_SPEED	(0.5)				//最短走行のスラローム速度	[m/s]
//#define FAST_SLA_ANG_SPEED		(26.18)		//最短走行のスラローム角速度      [rad/s]
//#define FAST_SLA_ANG_ACCEL		(440.0)		//最短走行のスラローム角加速度    [rad/s^2]

//#define FAST_SLA_SPEED	(0.6)				//最短走行のスラローム速度	[m/s]
//#define FAST_SLA_ANG_SPEED		(31.68)		//最短走行のスラローム角速度      [rad/s]
//#define FAST_SLA_ANG_ACCEL		(640.0)		//最短走行のスラローム角加速度    [rad/s^2]
//↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

#define FAST_ACCEL		(FAST_SLA_SPEED/((HALF_SECTION+SLA_STRAIGHT)/1000.0/FAST_SLA_SPEED))	//最短走行の加速度	[m/s^2]

#define MIN_SPEED	    (0.1)				//最低速度	[m/s]

#define TURN_ACCEL	    (PI*2)				//超信地旋回の加速度	[rad/s^2]
#define	TURN_SPEED	    (PI)				//超信地旋回の最高速度	[rad/s]
#define TURN_MIN_SPEED	(PI/10.0)			//超信地旋回の最低速度	[rad/s]

#define WAIT_TIME	10				//各動作後の待機時間	[ms]

//迷路関連パラメータ
#define GOAL_X	2		//ゴール座標(x)
#define GOAL_Y	0		//ゴール座標(y)

//決定用センサパラメータ
#define	SEN_DECISION	2000	//メニュー決定用の光センサ閾値

#define _PARAMETER

#endif
