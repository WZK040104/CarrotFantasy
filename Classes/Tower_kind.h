#ifndef __TOWER__KIND__H__
#define __TOWER__KIND__H__

#include "CTower.h"
#include <ctime>  // 用于时间相关的操作
#include <vector>

using namespace std;

extern int tower0_upgrade_coins[MAXlevel + 1];
extern int tower0_attack[MAXlevel + 1];
extern double tower0_attack_range[MAXlevel + 1];

extern int tower1_upgrade_coins[MAXlevel + 1];
extern int tower1_attack[MAXlevel + 1];
extern double tower1_attack_range[MAXlevel + 1];

extern int tower2_upgrade_coins[MAXlevel + 1];
extern int tower2_attack[MAXlevel + 1];
extern double tower2_attack_range[MAXlevel + 1];

extern int tower3_upgrade_coins[MAXlevel + 1];
extern int tower3_attack[MAXlevel + 1];
extern double tower3_attack_range[MAXlevel + 1];

class Tower0 : public CTower
{
public:
    Tower0();
    virtual ~Tower0();
};

class Tower1 : public CTower
{
public:
    Tower1();
    virtual ~Tower1();
};

class Tower2 : public CTower
{
public:
    Tower2();
    virtual ~Tower2();
};

class Tower3 : public CTower
{
public:
    Tower3();
    virtual ~Tower3();
	bool attack(vector<CEnemy*>& enemy, int damage_per_time, CEnemy* &target) override
	{
		if (!enemy.empty()) 
		{
			// 用于存储所有在攻击范围内的怪物
			vector<CEnemy*> enemiesInRange;

			// 寻找所有在攻击范围内的怪物
			for (auto it = enemy.begin(); it != enemy.end(); it++)
			{
				if (inRange(*it))
				{
					enemiesInRange.push_back(*it);
				}
			}

			for (auto it = enemiesInRange.begin(); it != enemiesInRange.end(); it++)
			{
				(*it)->HP_calculate(getDamage());	// 实施攻击
			}
			return true;
		}
		return false;
	}
};
#endif