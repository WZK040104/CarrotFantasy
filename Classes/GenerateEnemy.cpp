#include"CEnemy.h"
#include"Enemy_kind.h"
#include<vector>
using namespace std;

vector<CEnemy> EnemyExist;

void generateEnemy(vector<CEnemy>& EnemyExist, int enemyType, int x, int y)//在怪物出生点生成一只怪物
{
	CEnemy* newEnemy = nullptr;

    // 根据 enemyType 创建不同类型的防御塔
    switch (enemyType) {
        case 0:
            newEnemy = new Enemy0();
            break;
        case 1:
            newEnemy = new Enemy1();
            break;
        case 2:
            newEnemy = new Enemy2();
            break;
        case 3:
            newEnemy = new Enemy3();
            break;
        case 4:
            newEnemy = new Enemy4();
            break;

        default:
            // 不支持的防御塔类型
            break;
    }

    if (newEnemy)
    {
        EnemyExist.push_back(*newEnemy);
        delete newEnemy;
    }
}