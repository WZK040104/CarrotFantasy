#pragma once
#include "CTower.h"
#include <ctime>  // 用于时间相关的操作
#include <vector>
using namespace std;

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