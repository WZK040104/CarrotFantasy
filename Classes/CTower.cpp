#include "CTower.h"
#include "CEnemy.h"
#include <ctime>  // ����ʱ����صĲ���
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

// ���÷�����λ��
void CTower::setPosition(int x, int y)
{
	tower_position_x = x;
	tower_position_y = y;
}

int CTower::getType()const
{
	return Type;
}

// ��ȡ������λ��
double CTower::getPositionX()
{
	return tower_position_x;
}
double CTower::getPositionY()
{
	return tower_position_y;
}

// ��ȡ�������ȼ�
int CTower::getLevel()
{
	return tower_level;
}

// ��ȡ�������˺�(��ȼ��й�)
int CTower::getDamage()
{
	return damage_per_time[getLevel()];
}

// ��ȡ������������Χ(��ȼ��й�)
int CTower::getAttackRange() 
{
	return attck_range[getLevel()];
}

// ��ȡ�������������(��ȼ��й�)
int CTower::getUpgradeCost()
{
	return coins_to_level_up[getLevel()];
}

// ���������Ľ��
bool CTower::upgrade(int & gold_coins)
{
	if (gold_coins - getUpgradeCost() >= 0) {
		gold_coins -= getUpgradeCost();
		tower_level++;
		return true;
	}
	else
		return false;
}

// �����Ƿ��ڹ�����Χ��
bool CTower::inRange(CEnemy* enemy)
{
	if ((enemy->EnemyPositionX() - getPositionX()) * (enemy->EnemyPositionX() - getPositionX()) +
		(enemy->EnemyPositionY() - getPositionY()) * (enemy->EnemyPositionY() - getPositionY())
		<= getAttackRange() * getAttackRange())
		return true;
	else
		return false;
}

// Ѱ�Ҿ����ܲ�����ĵ���
CEnemy* nearestEnemy(vector<CEnemy*>& enemy, int positionx,int positiony)
{
	if (enemy.empty()) 
	{
		return nullptr;
	}

	CEnemy* nearest = enemy[0];
	for (unsigned int i = 1; i < enemy.size(); i++)
	{
		if ((enemy[i]->EnemyPositionX() - positionx) * (enemy[i]->EnemyPositionX() - positionx) 
			+ (enemy[i]->EnemyPositionY() - positiony) * (enemy[i]->EnemyPositionY() - positiony) 
			< (nearest->EnemyPositionX() - positionx) * (nearest->EnemyPositionX() - positionx) 
			+ (nearest->EnemyPositionY() - positiony) * (nearest->EnemyPositionY() - positiony))
			nearest = enemy[i];
	}
	return nearest;
}

// ���������Լ�����ĵ��˲���Ѫ
bool CTower::attack(vector<CEnemy*>& enemy, int damage_per_time, CEnemy* &target)
{
	if (!enemy.empty())
	{
		// ���ڴ洢�����ڹ�����Χ�ڵĹ���
		vector<CEnemy*> enemiesInRange;

		// Ѱ�������ڹ�����Χ�ڵĹ���
		for (auto it = enemy.begin(); it != enemy.end();it++)
		{
			if (inRange(*it))
			{
				enemiesInRange.push_back(*it);
			}
		}
		target = nearestEnemy(enemiesInRange, 75, 420);

		return true;
	}
	return false;
}