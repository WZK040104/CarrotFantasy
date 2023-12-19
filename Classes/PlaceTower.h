#pragma once
#include"CTower.h"
#include"Tower_kind.h"
#include<vector>
#include"cocos2d.h"

extern vector<CTower> TowerExist;

void placeTower(vector<CTower>& TowerExist, int towerType, int x, int y);