#ifndef __TOWER__KIND__H__
#define __TOWER__KIND__H__

#include "CTower.h"
#include <ctime>  // 用于时间相关的操作
#include <vector>

using namespace std;

extern int tower0_upgrade_coins[MAXlevel + 1];
extern int tower0_attack[MAXlevel + 1];
extern double tower0_timebetween_attack[MAXlevel + 1];
extern double tower0_attack_range[MAXlevel + 1];

extern int tower1_upgrade_coins[MAXlevel + 1];
extern int tower1_attack[MAXlevel + 1];
extern double tower1_timebetween_attack[MAXlevel + 1];
extern double tower1_attack_range[MAXlevel + 1];

extern int tower2_upgrade_coins[MAXlevel + 1];
extern int tower2_attack[MAXlevel + 1];
extern double tower2_timebetween_attack[MAXlevel + 1];
extern double tower2_attack_range[MAXlevel + 1];

extern int tower3_upgrade_coins[MAXlevel + 1];
extern int tower3_attack[MAXlevel + 1];
extern double tower3_timebetween_attack[MAXlevel + 1];
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
	void attack(vector<CEnemy>& enemy, int damage_per_time) override
	{
		if (!enemy.empty()) 
		{
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

			double currentTime = clock();
			double deltaTime = static_cast<double>(currentTime - get_last_attack_Time()) 
				/ CLOCKS_PER_SEC * 1000;	// 计算距离上一次攻击的时间间隔（毫秒）

			for (auto& enemy : enemy)
			{
				// 如果攻击冷却时间已过，并且怪物在攻击范围内
				if (deltaTime >= getTimeCooldown())
				{
					enemy.HP_calculate(getDamage());	// 实施攻击
					resetCooldown();					// 重置冷却时间
				}
			}
		}
	}
};
#endif