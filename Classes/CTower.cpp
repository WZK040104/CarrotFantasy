#include "CTower.h"
#include "CEnemy.h"
//#include "cocos2d.h"
#include <ctime>  // ����ʱ����صĲ���
#include <vector>
using namespace std;

//���÷�����λ��
void CTower::setPosition(int x, int y)
{
	tower_position_x = x;
	tower_position_y = y;
}

int CTower::getType()const
{
	return Type;
}
//��ȡ������λ��
double CTower::getPositionX()
{
	return tower_position_x;
}
double CTower::getPositionY()
{
	return tower_position_y;
}

//��ȡ�������ȼ�
int CTower::getLevel()const
{
	return tower_level;
}

//��ȡ�������˺�(��ȼ��й�)
int CTower::getDamage()const
{
	return damage_per_time[getLevel()];
}

//��ȡ������������Χ(��ȼ��й�)
int CTower::getAttackRange() const
{
	return attck_range[getLevel()];
}

//��ȡ�������������(��ȼ��й�)
int CTower::getUpgradeCost()const
{
	return coins_to_level_up[getLevel()];
}
//��ȡ�������������
double CTower::getTimeCooldown() const
{
	return time_between_attack[getLevel()];
}

//���������Ľ��
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

//�����Ƿ��ڹ�����Χ��
bool CTower::inRange(CEnemy& enemy)
{
	if ((enemy.EnemyPositionX() - getPositionX()) * (enemy.EnemyPositionX() - getPositionX()) + 
		(enemy.EnemyPositionY() - getPositionY()) * (enemy.EnemyPositionY() - getPositionY()) 
		<= getAttackRange() * getAttackRange())
		return true;
	else
		return false;
}

//��ȡ�������ϴι�������ʱ��
double CTower::get_last_attack_Time()
{
	return last_attack_Time;
}

//��������˺�ʱ���Ϊ��ǰʱ��
void CTower::resetCooldown()
{
	last_attack_Time = std::clock();
}

//Ѱ�Ҿ����ܲ�����ĵ���
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

//���������Լ�����ĵ��˲���Ѫ
void CTower::attack(vector<CEnemy>& enemy, int damage_per_time)
{
	if (!enemy.empty()) {
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
		
		CEnemy* target = nearestEnemy(enemiesInRange, 0, 0);	//�ܲ���λ����ʱδ������������������������������������
		double currentTime = clock();
		double deltaTime = static_cast<double>(currentTime - last_attack_Time) / CLOCKS_PER_SEC * 1000;	// ���������һ�ι�����ʱ���������룩

		// ���������ȴʱ���ѹ������ҹ����ڹ�����Χ��
		if (deltaTime >= getTimeCooldown())
		{
			target->HP_calculate(getDamage());	// ʵʩ����
			resetCooldown();					// ������ȴʱ��
		}
		
	}
}
