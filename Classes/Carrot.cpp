#include "Carrot.h"
using namespace std;

int coins[MAXLEVEL+1] = { 0, 20, 40, 80 };	//1����2����Ҫ�Ľ��Ϊ coins[1] 
int carrot_health[MAXLEVEL + 1] = { 0,20,25,30};//1����Ѫ��Ϊ carrot_health[1] 

int Carrot::getLevel()//��ǰ�ȼ� 
{
    return carrot_level;
}

int Carrot::getUpgradeCost()//��ǰ�ȼ�������Ǯ 
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

