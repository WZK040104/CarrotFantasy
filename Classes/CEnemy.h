#pragma once
#include"cocos2d.h"

class CEnemy	//��������� ����
{
private:
	int enemy_HP;				//������������ֵ����
	int HP;						//��ǰ��������ֵ
	float velocity;				//�ƶ��ٶ�
	int add_coins;				//������֮�����ӵĽ��
	double enemy_position_x;	//����ĺ�����
	double enemy_position_y;	//�����������
	
public:
	//���캯��
	CEnemy();
	
	// ��������
	virtual ~CEnemy();
	//��ʼ�����������ֵ,�ٶȣ����
	void initial(int input_type,int input_HP, float input_velocity, int input_coins, double x, double y); 
	//�Ƿ����
	bool alive(); 

	double EnemyPositionX();
	double EnemyPositionY();
	void set_x(double input_x);
	void set_y(double input_y);
	void HP_calculate(int damage_per_time);
	void setHP();
	float get_velocity();
	float getHPpercentage();
	int enemytype;
	cocos2d::Sprite* enemySprite; //����ľ���
	cocos2d::Sprite* getSprite();
	cocos2d::ProgressTimer* enemyHealthbar;//����Ѫ��
	cocos2d::Sprite* enemyHealthbar_back;
	//cocos2d::Sprite* getHealthbar();
	//cocos2d::Sprite* getHealthbar_back();
};

