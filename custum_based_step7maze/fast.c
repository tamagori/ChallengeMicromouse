
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
//�����̍��Wx,y�Ɍ������čŒZ���s����

	t_direction glob_nextdir;
	int straight_count=0;

	//���݂̌�������A���ɍs���ׂ������֌���
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
	{
		case front:
			straight_count++;			//�O�����������ꍇ�͒����𑖂鋗����L�΂�
			break;
		
		case right:					//�E�Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//�E�ɋȂ�����
			straight_count = 1;
			break;
		
		case left:					//���Ɍ���
			turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
			straight_count = 1;
			break;
		
		case rear:					//���Ɍ���
			turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;	//�����̌������X�V


	//�����������ɂ���Ď����̍��W���X�V����
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//�k������������Y���W�𑝂₷
			break;
			
		case east:
			mypos.x++;	//��������������X���W�𑝂₷
			break;
			
		case south:
			mypos.y--;	//�������������Y���W�����炷
			break;
		
		case west:
			mypos.x--;	//�����������Ƃ���X���W�����炷
			break;

	}


	
	while((mypos.x != x) || (mypos.y != y)){			//�S�[������܂ŌJ��Ԃ�


		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
		{
			case front:					//�������܂Ƃ߂đ���悤�ɂ���
				straight_count++;
				break;
			
			case right:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(90,TURN_ACCEL,TURN_SPEED,RIGHT);				//�E�ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
			
			case left:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(90,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
			
			case rear:
				straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
				turn(180,TURN_ACCEL,TURN_SPEED,LEFT);				//���ɋȂ�����
				straight_count = 1;			//���钼���̋��������Z�b�g
				break;
		}
	
		mypos.dir = glob_nextdir;	//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
				break;

		}
	}
	straight(SECTION*straight_count,FAST_ACCEL,FAST_SPEED,0.0);
}

void xyrad_run(int x, int y)
{
//�����̍��Wx,y�Ɍ������čŒZ���s����

	t_direction glob_nextdir;
	pos goal_pos;/*�ŏI�n�_*/
	pos line[18];/*�ڕW�O�� �� �ڕW�_�͂��̋O����̂ǂ����ɐݒ肷��*/
	int i;/*line �̗v�fNo*/
	char first_flg = 0;
	float x_def,y_def,l_def;
	float least_def;
	char least_flg;
	char st = 0;
	
	/*�O���[�o���ϐ��̏�����*/
	target_pos.x = 0;/*�����l*/
	target_pos.y = 0;/*�����l*/
	near_pos.x = 0;/*�����l*/
	near_pos.y = 0;/*�����l*/
	now_pos.x = 0;/*�����l*/
	now_pos.y = 0;/*�����l*/
	old_pos.x = 0;
	old_pos.y = 0;
	radian = 0;
	ang_target = 0; /*�ڕW�p�x*/
	ang_def = 0; /*�ڕW�p�x�ƌ��݊p�x�Ƃ̊p�x��*/
	old_len_def = 0;
	old_ang_def = 0;
	
	/*auto�ϐ��̏�����*/
	goal_pos.x = x*SECTION;/*X���S�[�����W[mm]*/
	goal_pos.y = y*SECTION;/*Y���S�[�����W[mm]*/
	
	/*�O���̏�����*/
	for(i=0;i<18;i++)
	{
		line[i].x = 0;
		line[i].y = 0;
	}
	
	/*���荞�ݏ������̃��[�h�I��*/
	run_mode = XYRAD_RUN;
	
	/*�S�[���܂ŌJ��Ԃ�*/
	while((goal_pos.x != near_pos.x) && (goal_pos.y != near_pos.y)){	

		(void)get_nextdir(x,y,MASK_SECOND,&glob_nextdir);	//������k�̏�񂾂��~����
		
		mypos.dir = glob_nextdir;	//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				for(i = 0;i<9;i++)
				{
					/*X���ω��Ȃ�*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x;
					/*Y��+����*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y + 10;
				}
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				for(i = 0;i<9;i++)
				{
					/*X��+����*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x + 10;
					/*Y���ω��Ȃ�*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y;
				}
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				for(i = 0;i<9;i++)
				{
					/*X���ω��Ȃ�*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x;
					/*Y��-����*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y - 10;
				}
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
				for(i = 0;i<9;i++)
				{
					/*X��-����*/
					line[i].x = line[i+9].x;
					line[i+9].x = line[i+9-1].x - 10;
					/*Y���ω��Ȃ�*/
					line[i].y = line[i+9].y;
					line[i+9].y = line[i+9-1].y;
				}
				break;
			default:
				/*�����Ȃ�*/
				break;
		}
		
		while(first_flg == 1)
		{
			least_flg = 0;
			for(i=st;i<18;i++)
			{
				/*�ڕW�O����̓_�Ō��݈ʒu�ƍł������̋߂��_��T��*/
				x_def = line[i].x - now_pos.x;
				y_def = line[i].y - now_pos.y;
				/*�ڕW�_�܂ł̋���*/
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
			/*�ŋߖT�_�̎Z�o*/
			near_pos.x = line[st].x;
			near_pos.y = line[st].y;
			/*����K�[�h*/
			if(st+POINT_NUM > 17)
			{
				st = 17 - POINT_NUM;
			}
			/****************OUTPUT*****************/
			target_pos.x = line[st+POINT_NUM].x;
			target_pos.y = line[st+POINT_NUM].y;
			/****************OUTPUT*****************/
			wait_ms(RUN_CAL_CYCLE);/*��莞�ԑҋ@[ms]*/
			
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
