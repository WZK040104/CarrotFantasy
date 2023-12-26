#ifndef __CARROT__H__
#define __CARROT__H__

#include <vector>
#define MAXLEVEL 3
using namespace std;

extern int coins[MAXLEVEL + 1];	//升级需要的金币
extern int carrot_health[MAXLEVEL +1];

class Carrot	//萝卜属性
{
private:
	int carrot_level;
	int HP;
public:
	Carrot() :carrot_level(1), HP(20) {}
	virtual ~Carrot() {};
	bool upgrade(int& gold_coins);	//升级
	int getLevel();			//获取等级
	int getUpgradeCost();		//获取升级需要的钱
};
#endif
