#include "CTower.h"
#include "CEnemy.h"
//#include "cocos2d.h"
#include <ctime>  // 用于时间相关的操作
#include <vector>
using namespace std;

//设置防御塔位置
void CTower::setPosition(int x, int y)
{
	tower_position_x = x;
	tower_position_y = y;
}

int CTower::getType()const
{
	return Type;
}
//获取防御塔位置
double CTower::getPositionX()
{
	return tower_position_x;
}
double CTower::getPositionY()
{
	return tower_position_y;
}

//获取防御塔等级
int CTower::getLevel()const
{
	return tower_level;
}

//获取防御塔伤害(与等级有关)
int CTower::getDamage()const
{
	return damage_per_time[getLevel()];
}

//获取防御塔攻击范围(与等级有关)
int CTower::getAttackRange() const
{
	return attck_range[getLevel()];
}

//获取防御塔升级金币(与等级有关)
int CTower::getUpgradeCost()const
{
	return coins_to_level_up[getLevel()];
}
//获取防御塔攻击间隔
double CTower::getTimeCooldown() const
{
	return time_between_attack[getLevel()];
}

//升级并消耗金币
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

//敌人是否在攻击范围内
bool CTower::inRange(CEnemy& enemy)
{
	if ((enemy.EnemyPositionX() - getPositionX()) * (enemy.EnemyPositionX() - getPositionX()) + 
		(enemy.EnemyPositionY() - getPositionY()) * (enemy.EnemyPositionY() - getPositionY()) 
		<= getAttackRange() * getAttackRange())
		return true;
	else
		return false;
}

//获取防御塔上次攻击结束时间
double CTower::get_last_attack_Time()
{
	return last_attack_Time;
}

//攻击完敌人后将时间记为当前时间
void CTower::resetCooldown()
{
	last_attack_Time = std::clock();
}

//寻找距离萝卜最近的敌人
CEnemy* nearestEnemy(vector<CEnemy*>& enemy, int positionx,int positiony)
{
	if (enemy.empty()) 
	{
		return nullptr;
	}

	CEnemy* nearest = enemy[0];
	for (int i = 1; i < enemy.size(); i++)
	{
		if ((enemy[i]->EnemyPositionX() - positionx) * (enemy[i]->EnemyPositionX() - positionx) 
			+ (enemy[i]->EnemyPositionY() - positiony) * (enemy[i]->EnemyPositionY() - positiony) 
			< (nearest->EnemyPositionX() - positionx) * (nearest->EnemyPositionX() - positionx) 
			+ (nearest->EnemyPositionY() - positiony) * (nearest->EnemyPositionY() - positiony))
			nearest = enemy[i];
	}
	return nearest;
}

//攻击距离自己最近的敌人并扣血
void CTower::attack(vector<CEnemy>& enemy, int damage_per_time)
{
	if (!enemy.empty()) {
		// 用于存储所有在攻击范围内的怪物
		vector<CEnemy*> enemiesInRange;

		// 寻找所有在攻击范围内的怪物
		for (auto& enemy : enemy)
		{
			if (inRange(enemy))
			{
				enemiesInRange.push_back(&enemy);
			}
		}
		
		CEnemy* target = nearestEnemy(enemiesInRange, 0, 0);	//萝卜的位置暂时未定！！！！！！！！！！！！！！！！！
		double currentTime = clock();
		double deltaTime = static_cast<double>(currentTime - last_attack_Time) / CLOCKS_PER_SEC * 1000;	// 计算距离上一次攻击的时间间隔（毫秒）

		// 如果攻击冷却时间已过，并且怪物在攻击范围内
		if (deltaTime >= getTimeCooldown())
		{
			target->HP_calculate(getDamage());	// 实施攻击
			resetCooldown();					// 重置冷却时间
		}
		
	}
}
