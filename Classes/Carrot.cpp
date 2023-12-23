#include "Carrot.h"
using namespace std;

//获取防御塔等级
int Carrot::getLevel()const
{
	return carrot_level;
}

//获取防御塔升级金币(与等级有关)
int Carrot::getUpgradeCost()const
{
	return coins_to_level_up[getLevel()];
}

//升级并消耗金币
bool Carrot::upgrade(int & gold_coins)
{
	if (gold_coins - getUpgradeCost() >= 0) {
		gold_coins -= getUpgradeCost();
		carrot_level++;
		return true;
	}
	else
		return false;
}

int coins_to_level_up[MAXlevel + 1] = { 0,20,40,80,0 };
int carrot_health[MAXlevel] = {0,200,400,600};