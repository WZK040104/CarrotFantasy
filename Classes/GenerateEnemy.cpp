#include"CEnemy.h"
#include"Enemy_kind.h"
#include<vector>
using namespace std;

vector<CEnemy> EnemyExist;

void generateEnemy(vector<CEnemy>& EnemyExist, int enemyType, int x, int y)//�ڹ������������һֻ����
{
	CEnemy* newEnemy = nullptr;

    // ���� enemyType ������ͬ���͵ķ�����
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
            // ��֧�ֵķ���������
            break;
    }

    if (newEnemy)
    {
        EnemyExist.push_back(*newEnemy);
        delete newEnemy;
    }
}