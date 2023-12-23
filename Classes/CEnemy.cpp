#include"CEnemy.h"
#include"cocos2d.h"

CEnemy::CEnemy(): enemytype(0),enemy_HP(0), HP(0), velocity(0), add_coins(0), enemy_position_x(0), enemy_position_y(0) {}
CEnemy::~CEnemy() {
	if (enemySprite)
	{
		enemySprite->removeFromParent();
	}
};	// ��������ʱִ�е��������������ͷ���Դ

void CEnemy::initial(int input_type,int input_HP, float input_velocity, int input_coins,double x,double y) 
//��ʼ�����������ֵ,�ٶȣ���ң�������
{
	enemytype = input_type;
	enemy_HP = input_HP;	 //��ʼ�����������ֵ
	HP = enemy_HP;			 //��ǰ����ֵΪ��ʼ����
	velocity = input_velocity;
	add_coins = input_coins;
	enemy_position_x = x;
	enemy_position_y = y;

	switch (input_type)
	{
	case 1:
		enemySprite = cocos2d::Sprite::create("Enemy_one.png");
		break;
	case 2:
		enemySprite = cocos2d::Sprite::create("Enemy_two.png");
		break;
	case 3:
		enemySprite = cocos2d::Sprite::create("Enemy_three.png");
		break;
	case 4:
		enemySprite = cocos2d::Sprite::create("Enemy_four.png");
		break;
	default:
		break;
	}
	
	enemySprite -> setPosition(cocos2d::Vec2(400, 75));
}
bool CEnemy::alive()  //�Ƿ����
{
	if (HP <= 0)
	{
		//gold_coins += add_coins;
		return false;
	}
	return true;
}
double CEnemy::EnemyPositionX()
{
	return enemy_position_x;
}
double CEnemy::EnemyPositionY()
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
float CEnemy::get_velocity()
{
	return velocity;
}
//void CEnemy::update1()
//{
//	// ���ݹ�����ٶȺ�ʱ�������¹����λ��
//	double new_x;// �����ٶȺ�ʱ���������µĺ�����
//	double new_y;
//	if (alive())
//	{
//		if (EnemyPositionX() >= 260 && EnemyPositionY() == 75)
//			new_x = EnemyPositionX() - velocity * 0.01;
//		else if (EnemyPositionX() >= 259 && EnemyPositionY() >= 75 && EnemyPositionY() <= 245)
//			new_y = EnemyPositionY() + velocity * 0.01;
//		else if (EnemyPositionY() <= 246 && EnemyPositionX() < 261 && EnemyPositionX() > 102)
//			new_x = EnemyPositionX() - velocity * 0.01;
//		else if (EnemyPositionX() <= 102)
//		{
//			HP -= 10000;
//		}
//		set_x(new_x);
//		set_y(new_y);
//	}
//
//}
//
//void CEnemy::update2()
//{
//	// ���ݹ�����ٶȺ�ʱ�������¹����λ��
//	double new_x;// �����ٶȺ�ʱ���������µĺ�����
//	double new_y;
//	if (alive())
//	{
//		if (EnemyPositionX() >= 162 && EnemyPositionY() == 72)
//			new_x = EnemyPositionX() - velocity * 0.01;
//		else if (EnemyPositionX() >= 161 && EnemyPositionY() >= 72 && EnemyPositionY() <= 160)
//			new_y = EnemyPositionY() + velocity * 0.01;
//		else if (EnemyPositionY() <= 161 && EnemyPositionX() >= 161 && EnemyPositionX() <= 366)
//			new_x = EnemyPositionX() + velocity * 0.01;
//		else if (EnemyPositionX() <= 367 && EnemyPositionY() >= 160 && EnemyPositionY() <= 248)
//			new_y = EnemyPositionY() + velocity * 0.01;
//		else if (EnemyPositionY() <= 249 && EnemyPositionX() >= 120 && EnemyPositionX() <= 367)
//			new_x = EnemyPositionX() - velocity * 0.01;
//		else if (EnemyPositionX() <= 120 && EnemyPositionY() <= 249)
//		{
//			HP -= 10000;
//		}
//		set_x(new_x);
//		set_y(new_y);
//	}
//
//}

cocos2d::Sprite* CEnemy::getSprite()
{
	return enemySprite;
}