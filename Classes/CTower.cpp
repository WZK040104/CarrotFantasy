#include "CTower.h"
#include "CEnemy.h"
#include <ctime>  // 用于时间相关的操作
#include <vector>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

// 设置防御塔位置
void CTower::setPosition(int x, int y)
{
	tower_position_x = x;
	tower_position_y = y;
}

int CTower::getType()const
{
	return Type;
}

// 获取防御塔位置
double CTower::getPositionX()
{
	return tower_position_x;
}
double CTower::getPositionY()
{
	return tower_position_y;
}

// 获取防御塔等级
int CTower::getLevel()
{
	return tower_level;
}

// 获取防御塔伤害(与等级有关)
int CTower::getDamage()
{
	return damage_per_time[getLevel()];
}

// 获取防御塔攻击范围(与等级有关)
int CTower::getAttackRange() 
{
	return attck_range[getLevel()];
}

// 获取防御塔升级金币(与等级有关)
int CTower::getUpgradeCost()
{
	return coins_to_level_up[getLevel()];
}

// 升级并消耗金币
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

// 敌人是否在攻击范围内
bool CTower::inRange(CEnemy* enemy)
{
	if ((enemy->EnemyPositionX() - getPositionX()) * (enemy->EnemyPositionX() - getPositionX()) +
		(enemy->EnemyPositionY() - getPositionY()) * (enemy->EnemyPositionY() - getPositionY())
		<= getAttackRange() * getAttackRange())
		return true;
	else
		return false;
}

// 寻找距离萝卜最近的敌人
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

// 攻击距离自己最近的敌人并扣血
bool CTower::attack(vector<CEnemy*>& enemy, int damage_per_time, CEnemy* &target)
{
	if (!enemy.empty())
	{
		// 用于存储所有在攻击范围内的怪物
		vector<CEnemy*> enemiesInRange;

		// 寻找所有在攻击范围内的怪物
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