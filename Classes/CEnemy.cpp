#include"CEnemy.h"

CEnemy::CEnemy(): enemy_HP(0), HP(0), velocity(0), add_coins(0), enemy_position_x(0), enemy_position_y(0) {}
CEnemy::~CEnemy() {};	// 对象销毁时执行的清理工作，例如释放资源
int gold_coins = 0;

void CEnemy::initial(int input_HP, int input_velocity, int input_coins,double x,double y) 
//初始化怪物的生命值,速度，金币，出生点
{
	enemy_HP = input_HP;	 //初始化怪物的生命值
	HP = enemy_HP;			 //当前生命值为初始生命
	velocity = input_velocity;
	add_coins = input_coins;
	enemy_position_x = x;
	enemy_position_y = y;
}
bool CEnemy::alive()  //是否活着
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