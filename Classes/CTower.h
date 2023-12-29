#ifndef __TOWER__H__
#define __TOWER__H__

#include "CEnemy.h"
#include <vector>
#include"cocos2d.h"

#define MAXlevel 4

using namespace std;

class CTower	//防御塔属性
{
private:
	int Type;								//种类
	int tower_level;						//等级
	int coins_to_level_up[MAXlevel];		//升级需要的金币
	int damage_per_time[MAXlevel+1];		//每次攻击的伤害
	double attck_range[MAXlevel+1];			//攻击范围
	int tower_position_x;					//建筑的横坐标
	int tower_position_y;					//建筑的纵坐标
	bool group_damage;
	
public:
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
		}
		
		tower_position_x = -1;
		tower_position_y = -1;
		group_damage = 0;
	}

	~CTower() {
		// 对象销毁时执行的清理工作，例如释放资源
	}

	void initial(int type, int input_tower_level, int input_coins_to_level_up[],
		int input_damage_per_time[],double input_attck_range[],bool input_group_damage) //初始化
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

	bool upgrade(int& gold_coins);	// 升级
	virtual bool attack(vector<CEnemy*>& enemy, int damage_per_time, CEnemy* &target);	// 攻击
	void setPosition(int x, int y);	// 建筑安放坐标
	int getType() const;			// 获取种类
	int getLevel();					// 获取等级
	int getDamage();				// 获取伤害
	int getAttackRange();			// 获取攻击范围
	bool inRange(CEnemy* enemy);    // 敌人是否在范围内
	int getUpgradeCost();			// 获取升级需要的钱
	double getPositionX();		    // 获取x坐标
	double getPositionY();		    // 获取y坐标
	CEnemy* nearestEnemy(vector<CEnemy*>& enemy, int positionx, int positiony);
};
#endif