#pragma once
#include "CEnemy.h"
#include <vector>
#define MAXlevel 4
#include"cocos2d.h"
using namespace std;

class CTower	//防御塔属性
{
private:
	int Type;								//种类
	int tower_level;						//等级
	int coins_to_level_up[MAXlevel];		//升级需要的金币
	int damage_per_time[MAXlevel+1];		//每次攻击的伤害
	double time_between_attack[MAXlevel+1];	//每次攻击的时间间隔
	double attck_range[MAXlevel+1];			//攻击范围
	int tower_position_x;					//建筑的横坐标
	int tower_position_y;					//建筑的纵坐标
	double last_attack_Time;				// 上一次攻击时间
	bool group_damage;

	
public:
	// 构造函数
	CTower()
	{
		// 初始化
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
	// 析构函数
	~CTower() {
		// 对象销毁时执行的清理工作，例如释放资源
	}

	void initial(int input_tower_level, int input_coins_to_level_up[], int input_damage_per_time[],double input_time_between_attack[], double input_attck_range[],bool input_group_damage) //初始化怪物的生命值,速度，金币
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

	bool upgrade(int& gold_coins);	//升级
	virtual void attack(vector<CEnemy>& enemy,int damage_per_time);	//攻击
	void setPosition(int x, int y);	//建筑安放坐标
	int getType() const;			//获取种类
	int getLevel() const;			//获取等级
	int getDamage() const;			//获取伤害
	int getAttackRange() const;		//获取攻击范围
	bool inRange(CEnemy& enemy);//敌人是否在范围内
	int getUpgradeCost() const;		//获取升级需要的钱
	double getPositionX();		//获取x坐标
	double getPositionY();		//获取y坐标
	double getTimeCooldown() const;	//获取冷却时间
	void resetCooldown();			//冷却时间
	double get_last_attack_Time();	//上次攻击时间
};