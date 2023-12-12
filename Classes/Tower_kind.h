#pragma once
#include "CTower.h"
#include <ctime>  // ����ʱ����صĲ���
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
			// ���ڴ洢�����ڹ�����Χ�ڵĹ���
			vector<CEnemy*> enemiesInRange;

			// Ѱ�������ڹ�����Χ�ڵĹ���
			for (auto& enemy : enemy)
			{
				if (inRange(enemy))
				{
					enemiesInRange.push_back(&enemy);
				}
			}

			double currentTime = clock();
			double deltaTime = static_cast<double>(currentTime - get_last_attack_Time()) 
				/ CLOCKS_PER_SEC * 1000;	// ���������һ�ι�����ʱ���������룩

			for (auto& enemy : enemy)
			{
				// ���������ȴʱ���ѹ������ҹ����ڹ�����Χ��
				if (deltaTime >= getTimeCooldown())
				{
					enemy.HP_calculate(getDamage());	// ʵʩ����
					resetCooldown();					// ������ȴʱ��
				}
			}
		}
	}
};