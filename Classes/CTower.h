#ifndef __TOWER__H__
#define __TOWER__H__

#include "CEnemy.h"
#include <vector>
#include"cocos2d.h"

#define MAXlevel 4

using namespace std;

class CTower	//����������
{
private:
	int Type;								//����
	int tower_level;						//�ȼ�
	int coins_to_level_up[MAXlevel];		//������Ҫ�Ľ��
	int damage_per_time[MAXlevel+1];		//ÿ�ι������˺�
	double attck_range[MAXlevel+1];			//������Χ
	int tower_position_x;					//�����ĺ�����
	int tower_position_y;					//������������
	bool group_damage;
	
public:
	CTower()
	{
		// ��ʼ��
		tower_level = 0;
		for(int i=0;i< MAXlevel;i++)
		{
			coins_to_level_up[i] = 0;
		}
		for (int i = 0; i < MAXlevel+1; i++)
		{
			damage_per_time[i] = 0;
			attck_range[i] = 0;
		}
		
		tower_position_x = -1;
		tower_position_y = -1;
		group_damage = 0;
	}

	~CTower() {
		// ��������ʱִ�е��������������ͷ���Դ
	}

	void initial(int type, int input_tower_level, int input_coins_to_level_up[],
		int input_damage_per_time[],double input_attck_range[],bool input_group_damage) //��ʼ��
	{
		Type = type;
		tower_level= input_tower_level;
		for (int i = 0; i < MAXlevel; i++)
		{
			coins_to_level_up[i] = input_coins_to_level_up[i];
		}
		for (int i = 0; i < MAXlevel+1; i++)
		{
			damage_per_time[i] = input_damage_per_time[i];
			attck_range[i] = input_attck_range[i];
		}
		group_damage = input_group_damage;
	}

	bool upgrade(int& gold_coins);	// ����
	virtual bool attack(vector<CEnemy*>& enemy, int damage_per_time, CEnemy* &target);	// ����
	void setPosition(int x, int y);	// ������������
	int getType() const;			// ��ȡ����
	int getLevel();					// ��ȡ�ȼ�
	int getDamage();				// ��ȡ�˺�
	int getAttackRange();			// ��ȡ������Χ
	bool inRange(CEnemy* enemy);    // �����Ƿ��ڷ�Χ��
	int getUpgradeCost();			// ��ȡ������Ҫ��Ǯ
	double getPositionX();		    // ��ȡx����
	double getPositionY();		    // ��ȡy����
	CEnemy* nearestEnemy(vector<CEnemy*>& enemy, int positionx, int positiony);
};
#endif