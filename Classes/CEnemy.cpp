#include"CEnemy.h"

CEnemy::CEnemy(): enemy_HP(0), HP(0), velocity(0), add_coins(0), enemy_position_x(0), enemy_position_y(0) {}
CEnemy::~CEnemy() {};	// ��������ʱִ�е��������������ͷ���Դ
int gold_coins = 0;

void CEnemy::initial(int input_HP, int input_velocity, int input_coins,double x,double y) 
//��ʼ�����������ֵ,�ٶȣ���ң�������
{
	enemy_HP = input_HP;	 //��ʼ�����������ֵ
	HP = enemy_HP;			 //��ǰ����ֵΪ��ʼ����
	velocity = input_velocity;
	add_coins = input_coins;
	enemy_position_x = x;
	enemy_position_y = y;
}
bool CEnemy::alive()  //�Ƿ����
{
	if (HP <= 0)
	{
		gold_coins += add_coins;
		return false;
	}
	return true;
}
double CEnemy::EnemyPositionX() const
{
	return enemy_position_x;
}
double CEnemy::EnemyPositionY() const
{
	return enemy_position_y;
}
void CEnemy::HP_calculate(int damage_per_time)
{
	HP -= damage_per_time;
}
void CEnemy::set_x(double input_x)
{
	enemy_position_x = input_x;
}
void CEnemy::set_y(double input_y)
{
	enemy_position_y = input_y;
}