#ifndef __CARROT__H__
#define __CARROT__H__

#include <vector>
#define MAXLEVEL 3
using namespace std;

extern int coins[MAXLEVEL + 1];	//������Ҫ�Ľ��
extern int carrot_health[MAXLEVEL +1];

class Carrot	//�ܲ�����
{
private:
	int carrot_level;
	int HP;
public:
	Carrot() :carrot_level(1), HP(20) {}
	virtual ~Carrot() {};
	bool upgrade(int& gold_coins);	//����
	int getLevel();			//��ȡ�ȼ�
	int getUpgradeCost();		//��ȡ������Ҫ��Ǯ
};
#endif
