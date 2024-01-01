#include"CEnemy.h"
#include"cocos2d.h"

CEnemy::CEnemy(): enemytype(0),enemy_HP(0), HP(0), velocity(0), add_coins(0), 
				  enemy_position_x(0), enemy_position_y(0),slowed(false),slowedtime(0.0),dizzy(false),dizzytime(0.0) {}

CEnemy::~CEnemy() {
	if (enemySprite)
	{
		enemySprite->removeFromParent();
	}
};	// ��������ʱִ�е��������������ͷ���Դ

void CEnemy::initial(int input_type,int input_HP, float input_velocity, int input_coins,double x,double y) 
// ��ʼ�����������ֵ,�ٶȣ���ң�������
{
	enemytype = input_type;
	enemy_HP = input_HP;	 // ��ʼ�����������ֵ
	HP = enemy_HP;			 // ��ǰ����ֵΪ��ʼ����
	velocity = input_velocity;
	add_coins = input_coins;
	enemy_position_x = x;
	enemy_position_y = y;

	switch (input_type)
	{
	case -1:
		enemySprite = nullptr;
		enemyHealthbar= nullptr;
		enemyHealthbar_back= nullptr;
	case 0:
		enemySprite = cocos2d::Sprite::create("Enemy_one.png");
		enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png");
		enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("HealthBar.png"));
		dizzypic = cocos2d::Sprite::create("vertigo.png");
		break;
	case 1:
		enemySprite = cocos2d::Sprite::create("Enemy_one.png");
		enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png");
		enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("HealthBar.png"));
		dizzypic= cocos2d::Sprite::create("vertigo.png");
		break;
	case 2:
		enemySprite = cocos2d::Sprite::create("Enemy_two.png");
		enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png");
		enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("HealthBar.png"));
		dizzypic = cocos2d::Sprite::create("vertigo.png");
		break;
	case 3:
		enemySprite = cocos2d::Sprite::create("Enemy_three.png");
		enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png");
		enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("HealthBar.png"));
		dizzypic = cocos2d::Sprite::create("vertigo.png");
		break;
	case 4:
		enemySprite = cocos2d::Sprite::create("Enemy_four.png");
		enemyHealthbar_back = cocos2d::Sprite::create("CarrotHealthBack.png");
		enemyHealthbar = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("HealthBar.png"));
		dizzypic = cocos2d::Sprite::create("vertigo.png");
		break;
	default:
		break;
	}
}

// �Ƿ����
bool CEnemy::alive() 
{
	if (HP <= 0)
	{
		//gold_coins += add_coins;
		return false;
	}
	return true;
}

float CEnemy::getHPpercentage()
{
	float x = float(HP) / float(enemy_HP);
	return x;
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

cocos2d::Sprite* CEnemy::getSprite()
{
	return enemySprite;
}
int CEnemy::getadd_coins()
{
	return add_coins;
}