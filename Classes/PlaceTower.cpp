#include"CTower.h"
#include"Tower_kind.h"
#include<vector>
#include"cocos2d.h"

using namespace std;

vector<CTower> TowerExist;

void placeTower(vector<CTower>& TowerExist, int towerType, int x, int y)
{
    CTower* newTower = nullptr;

    // 根据 towerType 创建不同类型的防御塔
    switch (towerType) {
        case 0:
            newTower = new Tower0();
            break;
        case 1:
            newTower = new Tower1();
            break;
        case 2:
            newTower = new Tower2();
            break;
        case 3:
            newTower = new Tower3();
            break;

        default:
            // 不支持的防御塔类型
            break;
    }

    if (newTower) 
    {
        newTower->setPosition(x, y);
        TowerExist.push_back(*newTower);
        delete newTower;
    }
}