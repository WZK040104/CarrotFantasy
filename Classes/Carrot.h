#pragma once
#include <vector>
#define MAXlevel 4
#include"cocos2d.h"
using namespace std;

class Carrot	//防御塔属性
{
private:
	int carrot_level;						//等级
	int coins_to_level_up[MAXlevel + 1];	//升级需要的金币
	int carrot_health[MAXlevel];	    //萝卜血量
public:
	// 构造函数
	Carrot()
	{
		// 初始化
		carrot_level = 0;
		for (int i = 0; i < MAXlevel; i++) {
			coins_to_level_up[i] = 0;
			carrot_health[i] = 0;
		}
	}
	// 析构函数
	~Carrot() {
		// 对象销毁时执行的清理工作，例如释放资源
	}

	void initial(int input_carrot_level, int input_coins_to_level_up[],int input_carrot_health[])
	{
		carrot_level = input_carrot_level;
		for (int i = 0; i < MAXlevel+1; i++)
			coins_to_level_up[i] = input_coins_to_level_up[i];
		for (int i = 0; i < MAXlevel; i++)
			carrot_health[i] = input_carrot_health[i];
	}

	bool upgrade(int& gold_coins);	//升级
	int getLevel() const;			//获取等级
	int getUpgradeCost() const;		//获取升级需要的钱
};