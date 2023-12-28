#include"CTower.h"
#include"Tower_kind.h"
#include<vector>
#include"cocos2d.h"
#include<iostream>
using namespace std;

vector<CTower*> TowerExist;

void placeTower(vector<CTower*>& TowerExist, int towerType, int x, int y)
{
	CTower* newTower = nullptr;

	// 根据 towerType 创建不同类型的防御塔
	switch (towerType) {
	case 0:
		newTower = new Tower0();
		newTower->initial(0, 1, tower0_upgrade_coins, tower0_attack, tower0_attack_range, 0);
		break;
	case 1:
		newTower = new Tower1();
		newTower->initial(1, 1, tower1_upgrade_coins, tower1_attack, tower1_attack_range, 0);
		break;
	case 2:
		newTower = new Tower2();
		newTower->initial(2, 1, tower2_upgrade_coins, tower2_attack, tower2_attack_range, 0);
		break;
	case 3:
		newTower = new Tower3();
		newTower->initial(3, 1, tower3_upgrade_coins, tower3_attack, tower3_attack_range, 0);
		break;

	default:
		// 不支持的防御塔类型
		break;
	}

	if (newTower)
	{
		newTower->setPosition(x, y);
		TowerExist.push_back(newTower);
		cout << newTower->getType();
		cout << newTower->getDamage();
		cout << newTower->getType();
	}

}

