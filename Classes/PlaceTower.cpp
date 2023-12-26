#include"CTower.h"
#include"Tower_kind.h"
#include<vector>
#include"cocos2d.h"

using namespace std;

vector<CTower> TowerExist;

void placeTower(vector<CTower>& TowerExist, int towerType, int x, int y)
{
    CTower* newTower = nullptr;

    // ���� towerType ������ͬ���͵ķ�����
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
            // ��֧�ֵķ���������
            break;
    }

    if (newTower) 
    {
        newTower->setPosition(x, y);
        TowerExist.push_back(*newTower);
        delete newTower;
    }
}