#include "Carrot.h"
using namespace std;

int coins[MAXLEVEL+1] = { 0, 20, 40, 80 };	//1级升2级需要的金币为 coins[1] 
int carrot_health[MAXLEVEL + 1] = { 0,20,25,30};//1级的血量为 carrot_health[1] 

int Carrot::getLevel()//当前等级 
{
    return carrot_level;
}

int Carrot::getUpgradeCost()//当前等级升级的钱 
{
    return coins[getLevel()];
}

bool Carrot::upgrade(int& gold_coins)
{
    if (gold_coins - getUpgradeCost() >= 0) {
        gold_coins -= getUpgradeCost();
        carrot_level++;
        return true;
    }
    else
        return false;
}

