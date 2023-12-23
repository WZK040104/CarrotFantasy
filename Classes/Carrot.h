#pragma once
#include <vector>
#define MAXlevel 4
#include"cocos2d.h"
using namespace std;

class Carrot	//����������
{
private:
	int carrot_level;						//�ȼ�
	int coins_to_level_up[MAXlevel + 1];	//������Ҫ�Ľ��
	int carrot_health[MAXlevel];	    //�ܲ�Ѫ��
public:
	// ���캯��
	Carrot()
	{
		// ��ʼ��
		carrot_level = 0;
		for (int i = 0; i < MAXlevel; i++) {
			coins_to_level_up[i] = 0;
			carrot_health[i] = 0;
		}
	}
	// ��������
	~Carrot() {
		// ��������ʱִ�е��������������ͷ���Դ
	}

	void initial(int input_carrot_level, int input_coins_to_level_up[],int input_carrot_health[])
	{
		carrot_level = input_carrot_level;
		for (int i = 0; i < MAXlevel+1; i++)
			coins_to_level_up[i] = input_coins_to_level_up[i];
		for (int i = 0; i < MAXlevel; i++)
			carrot_health[i] = input_carrot_health[i];
	}

	bool upgrade(int& gold_coins);	//����
	int getLevel() const;			//��ȡ�ȼ�
	int getUpgradeCost() const;		//��ȡ������Ҫ��Ǯ
};