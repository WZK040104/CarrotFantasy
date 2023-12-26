#include"CEnemy.h"
#include"Enemy_kind.h"
#include"GenerateEnemy.h"
#include <vector>
#include <chrono> // for std::chrono::seconds
#include <thread> // for std::this_thread::sleep_for

using namespace std;

vector<CEnemy*> EnemyExist;

void GenerateEnemy::generateOneEnemy(vector<CEnemy*>& EnemyExist, int enemyType, double x, double y)//�ڹ������������һֻ����
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
            // ��֧�ֵĵ�������
            break;
    }

    if (newEnemy)
    {
		newEnemy->set_x(x);
		newEnemy->set_y(y);
        EnemyExist.push_back(newEnemy);
        delete newEnemy;
    }
}

// ɾȥ��ȥ�ĵ���
void GenerateEnemy::deleteEnemy(vector<CEnemy*>& EnemyExist)
{
	for (auto it = EnemyExist.begin(); it != EnemyExist.end();)
	{
		if (!(*it)->alive())
		{
			delete *it;
			it = EnemyExist.erase(it);
		}
		else
		{
			++it;
		}
	}
}

int GenerateEnemy::numofEnemyAlive(vector<CEnemy*>& EnemyExist)
{
	int num = 0;
	for (auto enemy : EnemyExist)
	{
		if (enemy->alive())
		{
			num++;
		}
	}
	return num;
}

// ����һ�����εĹ����ʼ����Ϊxy
void GenerateEnemy::generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y)
{
	for (unsigned int i = 0; i < Enemyflag[flag].size(); i++)
	{
		generateOneEnemy(EnemyExist, Enemyflag[flag][i], x, y);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}