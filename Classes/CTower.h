#pragma once
#include "CEnemy.h"
#include <vector>
#define MAXlevel 4
#include"cocos2d.h"
using namespace std;

class CTower	//����������
{
private:
	int Type;								//����
	int tower_level;						//�ȼ�
	int coins_to_level_up[MAXlevel];		//������Ҫ�Ľ��
	int damage_per_time[MAXlevel+1];		//ÿ�ι������˺�
	double time_between_attack[MAXlevel+1];	//ÿ�ι�����ʱ����
	double attck_range[MAXlevel+1];			//������Χ
	int tower_position_x;					//�����ĺ�����
	int tower_position_y;					//������������
	double last_attack_Time;				// ��һ�ι���ʱ��
	bool group_damage;

	
public:
	// ���캯��
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
			time_between_attack[i] = 100;
		}
		
		tower_position_x = -1;
		tower_position_y = -1;
		group_damage = 0;
		last_attack_Time = 0;
	}
	// ��������
	~CTower() {
		// ��������ʱִ�е��������������ͷ���Դ
	}

	void initial(int input_tower_level, int input_coins_to_level_up[], int input_damage_per_time[],double input_time_between_attack[], double input_attck_range[],bool input_group_damage) //��ʼ�����������ֵ,�ٶȣ����
	{
		tower_level= input_tower_level;
		for (int i = 0; i < MAXlevel; i++)
		{
			coins_to_level_up[i] = input_coins_to_level_up[i];
		}
		for (int i = 0; i < MAXlevel+1; i++)
		{
			damage_per_time[i] = input_damage_per_time[i];
			attck_range[i] = input_attck_range[i];
			time_between_attack[i] = input_time_between_attack[i];
		}
		group_damage = input_group_damage;
	}

	bool upgrade(int& gold_coins);	//����
	virtual void attack(vector<CEnemy>& enemy,int damage_per_time);	//����
	void setPosition(int x, int y);	//������������
	int getType() const;			//��ȡ����
	int getLevel() const;			//��ȡ�ȼ�
	int getDamage() const;			//��ȡ�˺�
	int getAttackRange() const;		//��ȡ������Χ
	bool inRange(CEnemy& enemy);//�����Ƿ��ڷ�Χ��
	int getUpgradeCost() const;		//��ȡ������Ҫ��Ǯ
	double getPositionX();		//��ȡx����
	double getPositionY();		//��ȡy����
	double getTimeCooldown() const;	//��ȡ��ȴʱ��
	void resetCooldown();			//��ȴʱ��
	double get_last_attack_Time();	//�ϴι���ʱ��
};