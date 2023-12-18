#include"CEnemy.h"
#include"Enemy_kind.h"
#include<vector>
#include <chrono> // for std::chrono::seconds
#include <thread> // for std::this_thread::sleep_for
using namespace std;

vector<CEnemy> EnemyExist;

void generateOneEnemy(vector<CEnemy>& EnemyExist, int enemyType, double x, double y)//�ڹ������������һֻ����
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
        EnemyExist.push_back(*newEnemy);
        delete newEnemy;
    }
}

void deleteEnemy(vector<CEnemy>& EnemyExist)//ɾȥ��ȥ�ĵ���
{
	for (int i = 0; i < EnemyExist.size(); i++)
	{
		if (EnemyExist[i].alive() == 0)
		{
			auto it = EnemyExist.begin() + i;
			EnemyExist.erase(it);
		}
	}
}

int numofEnemyAlive(vector<CEnemy>& EnemyExist)
{
	int num = 0;
	for (int i = 0; i < EnemyExist.size(); i++)
	{
		if (EnemyExist[i].alive() == 1)
		{
			num++;
		}
	}

	return num;
}

void generateflag(int flag, vector<vector<int>> Enemyflag, double x, double y)//����һ�����εĹ����ʼ����Ϊxy
{
	for (int i = 0; i < Enemyflag[flag].size(); i++)
	{
		generateOneEnemy(EnemyExist, Enemyflag[flag][i], x, y);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}